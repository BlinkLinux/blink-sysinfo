
# About

## Deps
- Qt5
- cmake
- g++
- gtest
- kmod
- lsb-release
- mesa-utils
- netstat-nat
- ninja-build
- pciutils
- usbutils
- udisks2
- libudisks2-qt5-dev

## Build
```bash
cmake -B build -G Ninja
cmake --build build
DESTDIR=dist ninja -C build install
```

Executable file located at `build/dist/usr/local/bin/sysinfo`.
