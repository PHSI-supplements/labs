#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/keyboardlab.pdf .
tar cvfL keyboardlab.tar *
mv keyboardlab.tar ..
zip keyboardlab.zip *
mv keyboardlab.zip ..
mv keyboardlab.pdf ..
cd ..

