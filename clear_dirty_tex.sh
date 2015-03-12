#!/bin/bash
# script run on Linux to delete all dirty files generated from latex
#

BIN_EXT=".bin" 
RES_EXT=".asm"

BIN_FILE="test_data/test"$1$BIN_EXT
RES_FILE="test_data/test"$1$RES_EXT

STRING="Hello World"
#print variable on a screen
#echo $BIN_FILE
#echo $RES_FILE

echo
echo ============
echo
cat $RES_FILE
