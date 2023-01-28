#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/pointerlab.pdf .
tar cvf pointerlab.tar *
mv pointerlab.tar ..
zip pointerlab.zip *
mv pointerlab.zip ..
mv pointerlab.pdf ..
cd ..
