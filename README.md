# Vinnie

[![Build Status](https://travis-ci.org/clpo13/vinnie.svg?branch=master)](https://travis-ci.org/clpo13/vinnie)
[![Build status](https://ci.appveyor.com/api/projects/status/31tdtw83tgdwh2gy?svg=true)](https://ci.appveyor.com/project/clpo13/vinnie)

**Vinnie** is a simple command-line tool to tell you some basic information about a vehicle based on its Vehicle Identification Number (VIN).

## Caveats

There are a handful of different VIN standards worldwide that aren't quite compatible. This tool uses information sourced from the United States National Highway Traffic Safety Administration (NHTSA) and will only return valid data for North American VINs (specifically, the relevant data can be found in [Title 49 of the Code of Federal Regulations](https://www.law.cornell.edu/cfr/text/49/part-565)). European VINs adhere more closely to [ISO 3779:2009](https://www.iso.org/standard/52200.html), which this tool doesn't implement.

Additionally, the NHTSA format was standardized in 1981, so earlier VINs likely won't work with this tool.

## Requirements

- C compiler (gcc, clang, MSVC, etc.)
- [Meson](http://mesonbuild.com/)
- [Ninja](https://ninja-build.org/)
- [Check](https://libcheck.github.io/check/) (optional, for unit testing)
- [Doxygen](http://www.doxygen.org/) and [Graphviz](https://www.graphviz.org/) (optional, for API documentation)

On Debian-based systems, you can install these requirements with:

```bash
sudo apt-get update
sudo apt-get install build-essential meson ninja-build check doxygen graphviz
```

## Building

```bash
meson build
cd build
ninja && ninja install
```

You can also call `ninja test` in the build directory to run the unit tests.

If you'd like to build the API documentation, install Doxygen and Graphviz and run `doxygen` in the same directory as this project's `Doxyfile`.

## Usage

Simply run `vinnie <VIN>` where VIN is a 17-digit Vehicle Identification Number. The program will tell you if it's a valid VIN and, if so, print some basic info about the car, such as the model year, manufacturer, region built, and so on.

## License

Vinnie is free to use, modify, distribute, etc. according to the terms of the [MIT License](LICENSE).
