# OpenCS Binary-to-Text library for C
Copyright (c) 2015 Open Communications Security. All rights reserved.

## Introduction

The OpenCS Binary-to-Text library for C (ocsbincodec-c) is a customizable
library capable of encode and decode binary values to plain text using multiple
standard and non-standard encodings schemes. It is a port of ocsbincodec-java (https://github.com/opencs/ocsbincodec-java).

This library was designed to be as flexible as possible. This means that the
implementations in this library will always favor flexibility first.

## Portability

This code is designed to be as portable as possible. This means that it is 
expected to work on almost all platforms that supports a few things from
C99 compiler. The current list of platforms includes:

* iOS;
* MacOS X;
* Linux;
* Windows;
* IBM z/OS;

## Version history

* 1.0.0:
  * First public version ported from ocsbincodec-java

## Features

* Multiple Binary-to-Text encondings
  * Binary (customizeble)
  * Hexadecimal (RFC4648, customizable)
  * Base32 (RFC4648, customizable)
  * Base64 (RFC4648, customizable)
* Custom alphabets
* Uniform interface for all encoders/decoders
* Compatible with C# 3.5 and higher (including Windows Phone)

## Licensing

This software is released under the *Modified BSD License*.

## FAQ

### Can I use this library on commercial software?

Yes. Just follow the license restrictions.

### This library uses external dependencies?

The library itself is a pure C99 program. The test program (ocsbincodec-test) is implemented in C++ and uses the library Google Test 1.7.0 (https://code.google.com/p/googletest/).

### What is the IDE used to develop this library?

The IDE used was Eclipse Luna with CDT installed.

### What is the primary OS used to develop this library?

It was developed on Linux first and ported to Windows (Mingw32) later.

### Why is the name of the files so strange?

The file names were choosen to be at most 8 characters long. This ensures the compatibility with z/OS dataset member names.

### How do I integrate this code into my iOS project?

Just copy the files under ocsbincodec-c/include and ocsbincodec-c/src into your project's source, add them to your XCode project.

C API's can be used directly by Objective-C code and, with minor adjusts, from Swift too (https://developer.apple.com/library/prerelease/ios/documentation/Swift/Conceptual/BuildingCocoaApps/InteractingWithCAPIs.html).

