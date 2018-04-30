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

#ifndef VINNIE_H
#define VINNIE_H

/**
 * @brief Contains command-line options and descriptions.
 * 
 * The contents of the struct are printed when the option `-h`/`--help`
 * is passed to the program.
 * 
 */
struct helptxt {
    /**
     * @brief Short and long versions of possible command-line options.
     */
    const char *opt;
    /**
     * @brief A description of the preceding command-line option.
     */
    const char *desc;
};

/**
 * @brief Maps model year codes to their respective 4-digit year.
 */
struct modelyear {
    /**
     * @brief Model year code (alphanumeric, except I, O, Q, U, Z, and 0).
     */
    const char *code;
    /**
     * @brief Four-digit year between 2010 and 2039.
     * 
     * The same set of characters is used for 1980-2009. Which year the code
     * represents is determined by position 7 of the VIN. If it's a letter, the
     * year in this struct applies. If it's a number, subtract 30 from the year.
     */
    const int year;
};

void parseVin(char *);

#endif
