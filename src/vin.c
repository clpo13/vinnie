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
 * @param  vin a 17-character Vehicle Identification Number
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
 * @param  vin a 17-character Vehicle Identification Number
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