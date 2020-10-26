#!/usr/bin/env bash

set -e
shopt -s extglob

./astyle.bash `find . -print | grep -P "^.*\.[h,c][p,s]?p?$"`
