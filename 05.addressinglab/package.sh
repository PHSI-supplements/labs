#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/addressinglab.pdf .
tar cvf addressinglab.tar *
mv addressinglab.tar ..
zip addressinglab.zip *
mv addressinglab.zip ..
mv addressinglab.pdf ..
cd ..

