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

#include "config.h"
#include "vin.h"
#include "vinnie.h"

/**
 * @brief The main entry point for the command-line program.
 * 
 * Basic usage is `vinnie <VIN>` where VIN is a 17-digit Vehicle Identification
 * Number to be parsed. The number will be checked for validity according to its
 * check digit (9th character) and some basic information about it will be printed
 * to stdout, such as the World Manufacturer Identifier (WMI), model year, and
 * unique vehicle identifier.
 * 
 * @param  argc number of arguments
 * @param  argv array of arguments
 * @return      program return code (0 for success or 1 for failure)
 */
int main(int argc, char **argv) {
    // Create a list of arguments to print when `--help` is passed
    const struct helptxt helptext[] = {
        {"VIN", "A 17-digit Vehicle Identification Number"},
        {"-h, --help", "Print this help text"},
        {"-v, --version", "Show program version and quit"},
        {NULL, NULL}
    };

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
 * @param vin a 17-digit Vehicle Identification Number
 */
void parseVin(char *vin) {
    // First section: WMI (3 chars, 1-3)
    char wmi[4];
    memcpy(wmi, &vin[0], 3);
    wmi[3] = '\0';
    printf("World Manufacturer Identifier: %s\n", wmi);

    // Second section: vehicle attributes (5 chars, 4-8)
    char va[6];
    memcpy(va, &vin[3], 5);
    va[5] = '\0';
    printf("Vehicle attributes: %s\n", va);

    // Third section: check digit (1 char, 9)
    char chk = vin[8];
    printf("Check digit: %c\n", chk);

    // Fourth section: model year (1 char, 10), plant code (1 char, 11), and
    // sequential identifier (6 char, 12-17)
    char my = vin[9];
    char pc = vin[10];
    char vis[7];
    memcpy(vis, &vin[11], 7);
    printf("Model year: %c\n", my);
    printf("Plant code: %c\n", pc);
    printf("Sequential identifier: %s\n", vis);
}