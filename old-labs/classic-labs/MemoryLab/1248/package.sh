#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/memorylab.pdf .
tar cvf memorylab.tar *
mv memorylab.tar ..
zip memorylab.zip * */* */*/*
mv memorylab.zip ..
mv memorylab.pdf ..
cd ..
