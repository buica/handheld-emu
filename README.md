# handheld-emu

handheld-emu is a work-in-progress, lightweight GameBoy emulator written in C++ and using modern C++ practices while still keeping the project low level and fast. It aims to provide a balance between performance and simplicity. The popular and trusted "Blargg's test ROMs" is used to verify correct emulator behavior.

## Features

- CMake-based cross-platform build
- Catch2 Unit testing with CTest (automatically fetched by CMake)
- 🚧 Full instruction accuracy in progress
- 🏗️ Modular to allow future GBColor exntensibility.

## Dependencies

- C++17 compatible compiler (gcc/clang on Linux/macOS, WSL2 on Windows)
- CMake (>= 3.15)
- SDL2 (development headers)

## Quick Build on macOS

- Clone repo and install dependencies

```bash
brew install cmake sdl2
git clone https://github.com/buica/handheld-emu.git
cd handheld-emu
```

- build and test

```bash
mkdir build && cd build
cmake ..
cmake --build .
ctest --output-on-failure
```
