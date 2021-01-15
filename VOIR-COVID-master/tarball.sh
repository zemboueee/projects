#!/bin/sh

echo "#####################"
echo "# TARBALL GENERATOR #"
echo "#####################"

tarball="ozamen.tar.gz"

echo "cleaning..."
echo "rm -f $tarball"
rm -f "$tarball"

echo "${tarball}:"
tar -cvf "$tarball" "src" "CMakeLists.txt" "README" "build.sh"
