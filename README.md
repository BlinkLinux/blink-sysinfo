
# About
Get system software and hardware information on Linux.

## Deps
- qtbase5-dev
- cmake
- g++
- googletest
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
```

Executable file is located at `build/src/app/sysinfo`.

## Copyright
This project is released under GNU General Public License which can be found in
[LICENSE](LICENSE) file.
