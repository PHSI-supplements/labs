#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/duplicatorlab.pdf .
tar cvf duplicatorlab.tar *
mv duplicatorlab.tar ..
zip duplicatorlab.zip *
mv duplicatorlab.zip ..
mv duplicatorlab.pdf ..
cd ..

