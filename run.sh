#!/bin/bash
if [ ! -d "./build" ]; then
  mkdir build
fi

cd build
cmake ..
make -j 11
# sudo make install
cd ../
./build/SomeApp