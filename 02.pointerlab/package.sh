#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/keyboardlab.pdf .
tar cvf keyboardlab.tar *
mv keyboardlab.tar ..
zip keyboardlab.zip *
mv keyboardlab.zip ..
rm keyboardlab.pdf
cd ..

