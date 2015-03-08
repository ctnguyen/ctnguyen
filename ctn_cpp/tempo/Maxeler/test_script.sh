#!/bin/bash
# script help to run test
# take one argument, the test number ex "01", "02" ..."25" 

BIN_EXT=".bin" 
RES_EXT=".asm"

BIN_FILE="test_data/test"$1$BIN_EXT
RES_FILE="test_data/test"$1$RES_EXT

STRING="Hello World"
#print variable on a screen
#echo $BIN_FILE
#echo $RES_FILE
./task2.exe $BIN_FILE
echo
echo ============
echo
cat $RES_FILE
