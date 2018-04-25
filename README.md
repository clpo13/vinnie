# Vinnie

[![Build Status](https://travis-ci.org/clpo13/vinnie.svg?branch=master)](https://travis-ci.org/clpo13/vinnie)
[![Build status](https://ci.appveyor.com/api/projects/status/31tdtw83tgdwh2gy?svg=true)](https://ci.appveyor.com/project/clpo13/vinnie)

**Vinnie** is a simple command-line tool to tell you a bit about a Vehicle Identification Number (VIN). It doesn't make any calls to a remote server, so it's usable offline.

## Requirements

- C compiler (gcc, clang, MSVC, etc.)
- [Meson](http://mesonbuild.com/)
- [Ninja](https://ninja-build.org/)

On Debian-based systems, you can install these requirements with:

```bash
sudo apt-get update
sudo apt-get install build-essential meson ninja-build
```

## Building

```bash
meson build
cd build
ninja && ninja install
```

## Usage

Simply run `vinnie <VIN>` where VIN is a 17-digit Vehicle Identification Number.

## License

Vinnie is free to use, modify, distribute, etc. according to the terms of the [MIT License](LICENSE).
