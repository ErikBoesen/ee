all: essay
essay:
	latexmk -pdf -pdflatex="pdflatex -interaction=nonstopmode --shell-escape" essay.tex  -f
clean:
	rm -fv *.{aux,bbl,blg,log,out,pdf,synctex.gz,pyg,fls,fdb_latexmk,toc}
