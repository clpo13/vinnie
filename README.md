# Vinnie

[![Build Status](https://travis-ci.org/clpo13/vinnie.svg?branch=master)](https://travis-ci.org/clpo13/vinnie)
[![Build status](https://ci.appveyor.com/api/projects/status/31tdtw83tgdwh2gy/branch/master?svg=true)](https://ci.appveyor.com/project/clpo13/vinnie/branch/master)

**Vinnie** is a simple command-line tool to tell you some basic information about a vehicle based on its vehicle identification number (VIN).

## Caveats

There are a handful of different VIN standards worldwide that aren't quite compatible. This tool uses information sourced from the United States National Highway Traffic Safety Administration (NHTSA) and will only return valid data for North American VINs (specifically, the relevant data can be found in [Title 49 of the Code of Federal Regulations](https://www.law.cornell.edu/cfr/text/49/part-565)). European VINs adhere more closely to [ISO 3779:2009](https://www.iso.org/standard/52200.html), which this tool doesn't implement.

Additionally, the NHTSA format was standardized in 1981, so earlier VINs likely won't work with this tool.

## Requirements

- C compiler (gcc, clang, etc.)
- GNU Autotools
- GNU Make
- [Check](https://libcheck.github.io/check/) (optional, for unit testing)
- [Doxygen](http://www.doxygen.org/) and [Graphviz](https://www.graphviz.org/) (optional, for API documentation)

On Debian-based systems, you can install these requirements with:

```bash
sudo apt-get update
sudo apt-get install build-essential check doxygen graphviz
```

## Building

```bash
autoreconf -iv
./configure
make && make install
```

You can also call `make check` in the build directory to run the unit tests.

If you'd like to build the API documentation, install Doxygen and Graphviz and run `doxygen` in the same directory as this project's `Doxyfile`.

## Usage

Simply run `vinnie <VIN>` where VIN is a 17-digit vehicle identification number. The program will tell you if it's a valid VIN and, if so, print some basic info about the car, such as the model year, manufacturer, region built, and so on.

## Contributions

This program is still under active development, so features are not likely to work as expected or described. Even so, if you find bugs, please file an issue in the project's [issue tracker](https://github.com/clpo13/vinnie/issues) or create a [pull request](https://help.github.com/articles/about-pull-requests) to fix it. I'll try to respond to either within a few days.

There's no set coding convention to adhere to, but I'd prefer it if any contributions matched the existing style of the source code (put opening braces on the same line as the class/function, don't omit braces for short if/then blocks, etc.). In other words, despite this being C, I indent like it's Java. ¯\\\_(ツ)_/¯

## License

Copyright (c) 2018-2019 Cody Logan.

Vinnie is free to use, modify, distribute, etc. according to the terms of the [MIT License](LICENSE).
