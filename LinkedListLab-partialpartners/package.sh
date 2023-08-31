#!/bin/sh

cd assignment
#pdflatex LinkedListLab
#bibtex LinkedListLab
pdflatex LinkedListLab
pdflatex LinkedListLab
mv LinkedListLab.pdf linkedlistlab.pdf
cd ../starter-code
cp ../assignment/linkedlistlab.pdf .
tar cvfL linkedlistlab.tar *
mv linkedlistlab.tar ..
zip linkedlistlab.zip *
mv linkedlistlab.zip ..
mv linkedlistlab.pdf ..
cd ..

