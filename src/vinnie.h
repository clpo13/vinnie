// Vinnie - simple VIN decoder
// Copyright (c) 2018-2019 Cody Logan
// SPDX-License-Identifier: MIT

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
