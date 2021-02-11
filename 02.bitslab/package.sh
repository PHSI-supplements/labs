#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/bitslab.pdf .
tar cvf bitslab.tar *
mv bitslab.tar ..
zip bitslab.zip *
mv bitslab.zip ..
rm bitslab.pdf
cd ..

