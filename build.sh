#!/bin/bash
ctags -R .;
[ -d "build" ] || mkdir build;
pushd build;
cmake ..;
make clean;
make all;
popd;
