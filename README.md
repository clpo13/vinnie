# Vinnie

**Vinnie** is a simple command-line tool to tell you a bit about a Vehicle Identification Number (VIN). It doesn't make any calls to a remote server, so it's usable offline.

## Requirements

- C compiler (gcc, clang, MSVC, etc.)
- Meson
- Ninja

## Building

```bash
meson build
cd build
ninja && ninja install
```

## License

Vinnie is free to use, modify, distribute, etc. according to the terms of the [MIT License](LICENSE).
