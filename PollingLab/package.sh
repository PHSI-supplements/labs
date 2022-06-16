#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/pollinglab.pdf .
tar cvf pollinglab.tar *
mv pollinglab.tar ..
zip pollinglab.zip * */*
mv pollinglab.zip ..
mv pollinglab.pdf ..
cd ..
