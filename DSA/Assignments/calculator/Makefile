# Makefile to compile C++ code and LaTeX document  
  
# C++ Compilation  
all: List report  
  
List: main.cpp  
	@g++ main.cpp -o test -std=c++17 -O2  
  
# LaTeX Compilation  
report: report.tex  
	@lualatex report.tex  
  
clean:  
	@rm -f List *.aux *.log *.pdf *.toc  
  
.PHONY: all clean  