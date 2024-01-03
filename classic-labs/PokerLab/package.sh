#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/pokerlab.pdf .
#tar cvf pokerlab.tar * equivalent-java/*
tar cvf pokerlab.tar *
mv pokerlab.tar ..
#zip pokerlab.zip *
zip pokerlab.zip * equivalent-java/*
mv pokerlab.zip ..
mv pokerlab.pdf ..
cd ..

