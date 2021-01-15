#!/bin/sh

git ls-files | while read f; do git blame --line-porcelain $f | grep '^author '; done | sort -f | uniq -ic | sort -n

if [ -d "build" ]; then
    cd build;
else
    mkdir build;
    cd build;
fi

cmake ..;

if [ $? -ne 0 ]; then
    cd ..;
    rm -rf build;
    mkdir build;
    cd build;
    cmake ..;
fi

make -j; cd ..;
