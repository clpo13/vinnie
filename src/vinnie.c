// Vinnie - simple VIN decoder
// Copyright (c) 2018-2019 Cody Logan
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "vin.h"
#include "vinnie.h"

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
        printf("Usage: %s VIN\n", PACKAGE_NAME);
        printf("Try 'vinnie --help' for more information.\n");
        return EXIT_FAILURE;
    }

    // Help requested
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        printf("Usage: %s [options] <VIN>\n", PACKAGE_NAME);
        for (int i = 0; helptext[i].opt; i++) {
            printf("  %-15s %s\n", helptext[i].opt, helptext[i].desc);
        }
        return EXIT_SUCCESS;
    }

    // Version requested
    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
        printf("%s\n", PACKAGE_STRING);
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
    printf("World manufacturer identifier: %s\n", wmi);

    // Second section: vehicle attributes (5 chars, pos 4-8)
    char va[6];
    memcpy(va, &vin[3], 5);
    va[5] = '\0';
    printf("Vehicle attributes: %s\n", va);

    // Third section: check digit (1 char, pos 9)
    char chk = vin[8];
    printf("Check digit: %c\n", chk);

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
