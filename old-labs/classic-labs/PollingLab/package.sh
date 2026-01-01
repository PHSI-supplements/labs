#!/bin/sh

cd assignment
make
cd ../starter-code-Arduino
cp ../assignment/pollinglab.pdf .
tar cvfL pollinglab-arduino.tar *
mv pollinglab-arduino.tar ..
zip pollinglab-arduino.zip * */*
mv pollinglab-arduino.zip ..
rm pollinglab.pdf
cd ../starter-code-PlatformIO
cp ../assignment/pollinglab.pdf .
tar cvfL pollinglab-platformio.tar *
mv pollinglab-platformio.tar ..
zip pollinglab-platformio.zip * */* */*/*
mv pollinglab-platformio.zip ..
mv pollinglab.pdf ..
cd ..
