#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/integerlab.pdf .
tar cvf integerlab.tar *
mv integerlab.tar ..
zip integerlab.zip *
mv integerlab.zip ..
mv integerlab.pdf ..
cd ..

