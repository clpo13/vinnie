#!/bin/sh

cd "${MESON_SOURCE_ROOT}"
if command -v doxygen >/dev/null 2>&1; then
  doxygen
else
  echo >&2 "Doxygen is not installed. API documentation will not be generated."
fi
