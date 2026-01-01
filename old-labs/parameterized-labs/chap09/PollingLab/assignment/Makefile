LAB = pollinglab

lab: *.tex
	pdflatex $(LAB)
	pdflatex $(LAB)

all: lab

clean:
	rm -f $(LAB).aux $(LAB).log $(LAB).out $(LAB).synctex.gz $(LAB).toc $(LAB).bbl $(LAB).blg $(LAB).fls $(LAB).fdb_latexmk

clear: clean
	rm $(LAB).pdf
