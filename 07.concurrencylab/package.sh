#!/bin/sh

cd assignment
make
cd ../starter-code
cp ../assignment/concurrencylab.pdf .
tar cvf concurrencylab.tar *
mv concurrencylab.tar ..
zip concurrencylab.zip *
mv concurrencylab.zip ..
rm concurrencylab.pdf
cd ..

