#!/bin/bash
# script run on Linux to delete all generated dirty files
# ATTENTION : be sure that the repository is clean (no working file in process)
# 
# http://stackoverflow.com/questions/4515586/clean-an-svn-checkout-remove-non-svn-files
#

svn status --no-ignore | grep '^[?I]' |  sed "s/^[?I] //" | xargs -I{} rm -rf "{}"

