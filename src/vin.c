// Vinnie - simple VIN decoder
// Copyright (c) 2018-2019 Cody Logan
// SPDX-License-Identifier: MIT

#include "vin.h"

/**
 * @brief Convert a given character to a corresponding number between 0 and 9.
 * 
 * The letters I, O, and Q are not used.
 * 
 * @param  c a character to convert to a digit
 * @return   a number between 0 and 9
 */
int transliterate(char c) {
    const char *alphanum = "0123456789.ABCDEFGH..JKLMN.P.R..STUVWXYZ";
    return indexOf(alphanum, c) % 10;
}

/**
 * @brief Calculate the check digit for a given VIN.
 * 
 * The weights used here are sourced from 49 CFR 565.15 Table IV, which can be
 * viewed online at https://www.law.cornell.edu/cfr/text/49/565.15.
 * 
 * @param  vin a 17-character vehicle identification number
 * @return     the value of the check digit (0-9 or X)
 */
char getCheckDigit(char *vin) {
    const char *map = "0123456789X";            // X is a stand-in for 10.
    const char *weights = "8765432X098765432";  // here too
    int sum = 0;
    for (int i = 0; i < 17; i++) {
        sum += transliterate(vin[i]) * indexOf(map, weights[i]);
    }
    return map[sum % 11];
}

/**
 * @brief Validate a given VIN by its length and check digit.
 * 
 * @param  vin a 17-character vehicle identification number
 * @return     true if the VIN is valid, false otherwise
 */
bool validate(char *vin) {
    if (strlen(vin) != 17) {
        return false;
    }
    return getCheckDigit(vin) == vin[8];
}

/**
 * @brief Get the index of a character in a string.
 * 
 * @param  string an arbitrary string
 * @param  c      the character to find in the string
 * @return        the position of the character within the string
 *                or -1 if not found
 */
int indexOf(const char *string, char c) {
    char *posc = strchr(string, c);
    int pos = posc ? posc - string : -1;
    return pos;
}
