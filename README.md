# c-tplink
code to control TP-Link IoT devices written in C

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