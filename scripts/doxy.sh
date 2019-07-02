#!/bin/sh
#
# Vinnie - simple VIN decoder
# Copyright (c) 2018-2019 Cody Logan
# SPDX-License-Identifier: MIT
#
# Documentation generation script.

cd "${MESON_SOURCE_ROOT}" || exit 1
if command -v doxygen >/dev/null 2>&1; then
  doxygen
else
  echo >&2 "Doxygen is not installed. API documentation will not be generated."
  exit 1
fi
