#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/pokerlab.pdf .
tar cvf pokerlab.tar *
mv pokerlab.tar ..
zip pokerlab.zip *
mv pokerlab.zip ..
rm pokerlab.pdf
cd ..

