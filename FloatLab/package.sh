#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/floatlab.pdf .
tar cvf floatlab.tar *
mv floatlab.tar ..
zip floatlab.zip *
mv floatlab.zip ..
mv floatlab.pdf ..
cd ..

