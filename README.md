# c-tplink
code to control TP-Link IoT devices written in C

## Purpose

1) Provide ability to control TP-Link IoT devices (switch and light bulb) using C.
2) Explore test driven development as described by J.W. Grenning in "Test-Driven Development for Embedded C" (This is not embedded code bit U have the book and the principles should work for code running under Linux and perhaps other operating systems.)
3) Compare this sort of developemnt with Go (as done with https://github.com/HankB/orvibo)

## Status
Initial effort will support a plug (HS100)
* (dummy) cppunit test implemented

## Requirements

* CppUTest (`https://github.com/cpputest/cpputest`) installed
  and built in the parent directory of this project. (Could be another
  directory if the CPPUTEST_HOME is set accordingly.)


## Procedure

``` run
cd c-tplink
export CPPUTEST_HOME=../cpputest
make
```