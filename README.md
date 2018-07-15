# appbricks [![Build Status](https://travis-ci.org/dus7eh/appbricks.svg?branch=master)](https://travis-ci.org/dus7eh/appbricks)

## 1. Intoduction
This project contains a number of <b>c++</b> classes and functions usefull for application development especially when using a pre c++14/17 compliant compiler.

## 2. Overview
In the current versions following components, further called bricks, are implemented:
 - *optional* - class handy for passing values which could be nullable  
 - *stringview* - which allows to perform read-only operations on sections of a larger string without copying the data 
 - *blob* - class which lets you store different types of data (similar to `boost::any`) 
 - *text* - a wrapper for `std::string` with a number of text transformation methods
 - *textutils* - set of text tranfromations implemented as free functions (these are used by the text wrapper)
 
 
Most of the above are header only implementations which makes using them in your own project painless.
For convenience cmake configuration is prepared. It lets you generate and compile the code with the toolchain of your choice.

## 3. Building
After downloading the project to generate build configuration simply call:

`cmake -G <generator_name> [-DCMAKE_INSTALL_PREFIX=<destination_dir>]`

To build and install the files to a specified directory run:

`cmake --build . --target install`

All of the created implementations are correlated with a set of unit tests.
This project utilizes [googletest](https://github.com/google/googletest) library for this purpose. You don't have to download and build gtest separately - it is accomplished via proper cmake configuration files.

Unit tests for the appbricks can be build and run by calling:

`cmake --build . --target tests`
`ctest`

## 4. Documentation
At this stage of the project there is no wiki page available.
Hence, the best way to see how a particular brick can be used is to analyse unit tests related to it.
Each brick has its own set of tests prepared in a distinct file.

So for example, if you're interested in `blob` class then check out `test_blob` source file for usage details.

## 5. Contribution
To make the development easier (at least for the UT part) there is an additional and optional `-DDEV_MODE=ON` parameter which can be specified on the cmake configuration stage.

This switch makes the unit tests work with the sources from repo dir structure. When not specified, unit tetst work against the files in the installation directory.
