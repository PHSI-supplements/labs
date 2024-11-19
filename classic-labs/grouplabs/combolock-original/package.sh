#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/combolock.pdf grouplab.pdf
tar cvf grouplab.tar *
mv grouplab.tar ../..
zip grouplab.zip * */*
mv grouplab.zip ../..
mv grouplab.pdf ../..
cd ..
