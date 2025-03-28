# Makefile to compile C++ code and LaTeX document

# Targets
all: test report

# C++ Compilation
test: test.cpp HeapSort.h
	@g++ -O2 -std=c++17 -o test test.cpp
	@echo "C++ compilation complete: test"

# LaTeX Compilation
report: report.tex
	@xelatex report.tex
	@echo "LaTeX compilation complete: report.pdf"

# Clean generated files
clean:
	@rm -f test *.aux *.log *.toc
	@echo "Cleaned up generated files."

# Phony targets
.PHONY: all clean
