// Vinnie - simple VIN decoder
// Copyright (c) 2018 Cody Logan
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdio.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "cJSON.h"
#include "config.h"
#include "vin.h"
#include "vinnie.h"

/**
 * @brief Struct to store data received from an HTTP request.
 */
struct MemoryStruct {
    /**
     * @brief Received data
     */
    char *memory;
    /**
     * @brief Size of received data
     */
    size_t size;
};

/**
 * @brief (Re)allocate enough memory to store a chunk of data.
 * 
 * This function is reused from the libcurl example
 * [getinmemory.c](https://curl.haxx.se/libcurl/c/getinmemory.html)
 * which is licensed according to the terms found in LICENSE-3RD-PARTY and at
 * <https://curl.haxx.se/docs/copyright.html>.
 * 
 * @param contents 
 * @param size 
 * @param nmemb 
 * @param userp 
 * @return size_t 
 */
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        // Out of memory
        fprintf(stderr, "not enough memory (realloc returned NULL)\n");
        return EXIT_FAILURE;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// Create a list of arguments to print when `--help` is passed
const struct helptxt helptext[] = {
    {"VIN", "A 17-digit vehicle identification number"},
    {"-h, --help", "Print this help text"},
    {"-v, --version", "Show program version and quit"},
    {NULL, NULL}
};

// Map codes to model years. If the character in position 7 is numeric,
// subtract 30 from the year given here.
const struct modelyear modelyear[] = {
    {"A", 2010}, {"B", 2011}, {"C", 2012}, {"D", 2013}, {"E", 2014}, {"F", 2015},
    {"G", 2016}, {"H", 2017}, {"J", 2018}, {"K", 2019}, {"L", 2020}, {"M", 2021},
    {"N", 2022}, {"P", 2023}, {"R", 2024}, {"S", 2025}, {"T", 2026}, {"V", 2027},
    {"W", 2028}, {"X", 2029}, {"Y", 2030}, {"1", 2031}, {"2", 2032}, {"3", 2033},
    {"4", 2034}, {"5", 2035}, {"6", 2036}, {"7", 2037}, {"8", 2038}, {"9", 2039},
    {NULL, 0}
};

/**
 * @brief The main entry point for the command-line program.
 * 
 * Basic usage is `vinnie <VIN>` where VIN is a 17-digit vehicle identification
 * number to be parsed. The number will be checked for validity according to its
 * check digit (9th character) and some basic information about it will be printed
 * to stdout, such as the world manufacturer identifier (WMI), model year, and
 * unique vehicle identifier.
 * 
 * @param  argc number of arguments
 * @param  argv array of arguments
 * @return      program return code (0 for success or 1 for failure)
 */
int main(int argc, char **argv) {
    // Need one argument
    if (argc < 2) {
        printf("Usage: %s VIN\n", PROJECT_NAME);
        printf("Try 'vinnie --help' for more information.\n");
        return EXIT_FAILURE;
    }

    // Help requested
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        printf("Usage: %s [options] <VIN>\n", PROJECT_NAME);
        for (int i = 0; helptext[i].opt; i++) {
            printf("  %-15s %s\n", helptext[i].opt, helptext[i].desc);
        }
        return EXIT_SUCCESS;
    }

    // Version requested
    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
        printf("%s %s\n", PROJECT_NAME, VERSION_STR);
        return EXIT_SUCCESS;
    }

    char *vin = argv[1];
    if (validate(vin)) {
        printf("VIN %s is valid!\n", vin);
        parseVin(vin);
    } else {
        printf("Invalid VIN. Please double-check your entry or try a different one.\n");
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Parse a given VIN into components that represent data about the vehicle.
 * 
 * @param vin a 17-digit vehicle identification number
 */
void parseVin(char *vin) {
    // First section: WMI (3 chars, pos 1-3)
    char wmi[4];
    memcpy(wmi, &vin[0], 3);
    wmi[3] = '\0';
    //printf("World manufacturer identifier: %s\n", wmi);
    getWMI(wmi);

    // Second section: vehicle attributes (5 chars, pos 4-8)
    char va[6];
    memcpy(va, &vin[3], 5);
    va[5] = '\0';
    printf("Vehicle attributes: %s\n", va);

    // Third section: check digit (1 char, pos 9)
    //char chk = vin[8];
    //printf("Check digit: %c\n", chk);

    // Fourth section: model year (1 char, pos 10), plant code (1 char, pos 11),
    // and sequential identifier (6 char, pos 12-17)
    char my = vin[9];
    int year = 0;
    for (int i = 0; modelyear[i].code; i++) {
        if (my == *modelyear[i].code) {
            year = modelyear[i].year;
        }
    } 
    // If position 7 in the VIN is a number, subtract 30 from the year.
    // ASCII dec 65 is the letter A, numbers 0-9 are less than that.
    if (vin[6] < 65) {
        year = year - 30;
    }
    char pc = vin[10];
    char vis[7];
    memcpy(vis, &vin[11], 7);
    printf("Model year: %i\n", year);
    printf("Plant code: %c\n", pc);
    printf("Sequential identifier: %s\n", vis);
}

/**
 * @brief Decode a world manufacturer identifier by querying the [NHTSA vPIC API](https://vpic.nhtsa.dot.gov/api/).
 * 
 * @param wmi a three-digit code representing a manufacturer
 */
void getWMI(char *wmi) {
    char *url = "https://vpic.nhtsa.dot.gov/api/vehicles/decodewmi/";
    char fullurl[256];
    snprintf(fullurl, sizeof(fullurl), "%s%s%s", url, wmi, "?format=json");
    //printf("Querying %s\n", fullurl);

    CURL *curl;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, fullurl);
        // Use a callback function to store received data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed %s\n", curl_easy_strerror(res));
        } else {
            // Print raw response data
            //printf("%s\n", chunk.memory);

            // Parse JSON
            const cJSON *results = NULL;
            const cJSON *result = NULL;
            cJSON *json = cJSON_Parse(chunk.memory);
            if (json == NULL) {
              const char *errorPtr = cJSON_GetErrorPtr();
              if (errorPtr != NULL) {
                fprintf(stderr, "Error before: %s\n", errorPtr);
              }
              cJSON_Delete(json);
              return;
            }

            // Get manufacturer, make, and vehicle type from JSON
            results = cJSON_GetObjectItemCaseSensitive(json, "Results");
            cJSON_ArrayForEach(result, results) {
              cJSON *manufacturer = cJSON_GetObjectItemCaseSensitive(result, "ManufacturerName");
              cJSON *make = cJSON_GetObjectItemCaseSensitive(result, "Make");
              cJSON *type = cJSON_GetObjectItemCaseSensitive(result, "VehicleType");

              if (!cJSON_IsString(manufacturer) || !cJSON_IsString(make) || !cJSON_IsString(type)) {
                cJSON_Delete(json);
                return;
              } else {
                printf("Manufacturer: %s\n", manufacturer->valuestring);
                printf("Make: %s\n", make->valuestring);
                printf("Type: %s\n", type->valuestring);
              }
            }

            cJSON_Delete(json);
        }

        // Cleanup request
        curl_easy_cleanup(curl);
    }

    // Clean up stored data
    free(chunk.memory);

    // Global cleanup
    curl_global_cleanup();
}
