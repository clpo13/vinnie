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

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "vinnie.h"

int main(int argc, char **argv) {
    // Need one argument
    if (argc < 2) {
        printf("Please input a Vehicle Identification Number.\n");
        printf("Try 'vinnie --help' for more information.\n");
        return 1;
    }

    // Help requested
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        printf("Usage:\n");
        printf("%s <VIN>\n", PROJECT_NAME);
        return 0;
    }

    // Version requested
    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
        printf("%s %s\n", PROJECT_NAME, VERSION_STR);
        return 0;
    }

    char *vin = argv[1];
    if (validate(vin)) {
        printf("Information for VIN %s:\n", vin);
    } else {
        printf("Invalid VIN\n");
    }

    return 0;
}

// Convert a given character to a corresponding number between 0 and 9.
// I, O, and Q are not used.
int transliterate(char c) {
    const char *alphanum = "0123456789.ABCDEFGH..JKLMN.P.R..STUVWXYZ";
    return indexOf(alphanum, c) % 10;
}

// Calculate the check digit for a given VIN.
char getCheckDigit(char *vin) {
    const char *map = "0123456789X";            // X is a stand-in for 10.
    const char *weights = "8765432X098765432";  // here too
    int sum = 0;
    for (int i = 0; i < 17; i++) {
        sum += transliterate(vin[i] * indexOf(map, weights[i]));
    }
    return map[sum % 11];
}

// Validate a given VIN by its length and check digit.
bool validate(char *vin) {
    if (strlen(vin) != 17) {
        return false;
    }
    return getCheckDigit(vin) == vin[8];
}

// Gets the index of a character in a string.
// Returns -1 if the character is not found.
int indexOf(const char *string, char c) {
    char *posc = strchr(string, c);
    int pos = posc ? posc - string : -1;
    return pos;
}