# Makefile to compile C++ code and LaTeX document  
  
# C++ Compilation  
all: List report  
  
List: List.cpp  
	@g++ List.cpp -o List -std=c++17 -O2  
  
# LaTeX Compilation  
report: report.tex  
	@xelatex report.tex  
  
clean:  
	@rm -f List *.aux *.log *.pdf *.toc  
  
.PHONY: all clean  