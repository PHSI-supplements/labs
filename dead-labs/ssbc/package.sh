#!/bin/sh

cd assignment
make

cd ../starter-code-1-warmup
cp ../assignment/ssbclab-warmup.pdf .
tar cvf ssbclab-warmup.tar *
mv ssbclab-warmup.tar ..
zip ssbclab-warmup.zip *
mv ssbclab-warmup.zip ..
rm ssbclab-warmup.pdf

cd ../starter-code-2-polling
cp ../assignment/ssbclab-polling.pdf .
tar cvf ssbclab-polling.tar *
mv ssbclab-polling.tar ..
zip ssbclab-polling.zip *
mv ssbclab-polling.zip ..
rm ssbclab-polling.pdf

cd ../starter-code-3-interrupts
cp ../assignment/ssbclab-interrupts.pdf .
tar cvf ssbclab-interrupts.tar *
mv ssbclab-interrupts.tar ..
zip ssbclab-interrupts.zip *
mv ssbclab-interrupts.zip ..
rm ssbclab-interrupts.pdf

cd ..

