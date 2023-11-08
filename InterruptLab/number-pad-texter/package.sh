#!/bin/sh

cd assignment
make
cd ../starter-code-Arduino
cp ../assignment/interruptlab.pdf .
tar cvfL interruptlab-arduino.tar *
mv interruptlab-arduino.tar ..
zip interruptlab-arduino.zip * */*
mv interruptlab-arduino.zip ..
rm interruptlab.pdf
cd ../starter-code-PlatformIO
cp ../assignment/interruptlab.pdf .
tar cvfL interruptlab-platformio.tar *
mv interruptlab-platformio.tar ..
zip interruptlab-platformio.zip * */* */*/*
mv interruptlab-platformio.zip ..
mv interruptlab.pdf ..
cd ..
