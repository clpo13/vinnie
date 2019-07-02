// Vinnie - simple VIN decoder
// Copyright (c) 2018-2019 Cody Logan
// SPDX-License-Identifier: MIT

#ifndef VIN_H
#define VIN_H

#include <stdbool.h>
#include <string.h>

int transliterate(char);
char getCheckDigit(char *);
bool validate(char *);
int indexOf(const char *, char);

#endif
