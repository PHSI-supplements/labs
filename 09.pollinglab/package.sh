#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/pollinglab.pdf .
zip pollinglab.zip * */*
mv pollinglab.zip ..
mv pollinglab.pdf ..
cd ..

