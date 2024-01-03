#!/bin/sh

cd assignment
make
cd ../starter-code-Arduino
cp ../assignment/rangefinder.pdf .
tar cvfL rangefinder-arduino.tar *
mv rangefinder-arduino.tar ..
zip rangefinder-arduino.zip * */*
mv rangefinder-arduino.zip ..
rm rangefinder.pdf
cd ../starter-code-PlatformIO
cp ../assignment/rangefinder.pdf .
tar cvfL rangefinder-platformio.tar *
mv rangefinder-platformio.tar ..
zip rangefinder-platformio.zip * */* */*/*
mv rangefinder-platformio.zip ..
mv rangefinder.pdf ..
cd ..
