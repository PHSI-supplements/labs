#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/interruptlab.pdf .
tar cvf interruptlab.tar *
mv interruptlab.tar ..
zip interruptlab.zip * */*
mv interruptlab.zip ..
mv interruptlab.pdf ..
cd ..
