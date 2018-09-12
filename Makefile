all: essay
essay:
	latexmk -pdf -pdflatex="pdflatex -interaction=nonstopmode --shell-escape" essay.tex  -f

