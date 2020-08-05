[![Build Status](https://travis-ci.org/Panky-codes/cpp-template.svg?branch=master)](https://travis-ci.org/Panky-codes/cpp-template)
## MoxC (Mocks C)
MoxC automatically generates mocks for C interface that can be used in a C++ unittest. It can generate mocks based on different open-source mocking frameworks. GMock and Troempeloeil (never get the spelling correct for this one) are currently supported.  

## Sneak Peak

## Install
### Precompiled binary (Available only for Linux for now)
## Build
### Dependencies
- GCC or Clang with C++17 support
- CMake
- Conan
- Ninja
- libclang

After downloading the sources from github, go to the project root and execute the following command:
```
~/MoxC$ cmake -GNinja -B build 
~/MoxC$ cmake --build build -- -j4
```
