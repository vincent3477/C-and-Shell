#
# Makefile for Assignment 3, CSE 13S, Fall 2022.
#
# You are welcome to modify this Makefile to meet your needs.
# You should learn from the Makefile, and try building your own!
#

# These are "phony" targets: they're not real files
.PHONY: all pdfs clean

##################################################################
#
# C stuff
#
##################################################################

# Name of the program this Makefile is going to build
EXECBIN  = play-dreidel

# Default values for compiling C files
CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra $(OPTFLAG)
# Optimization level
OPTFLAG  = -O2

# All available .c files are included as SOURCES
#SOURCES  = $(wildcard *.c)
# Specify the C source files manually. May be useful if you
# don't want to compile *all* the C files together.
SOURCES   = dreidel.c play-dreidel.c mtrand.c

# Each .c file has a corresponding .o file
OBJECTS  = $(SOURCES:%.c=%.o)

# This is the first actual target in the file.
# That means it's built when 'make' is run without arguments.
all: $(EXECBIN)
# If you want to build the pdf files as well as the executable (if needed),
# use the following line:
# all: $(EXECBIN) pdfs

# The program depends on *all* of the OBJECTS.
$(EXECBIN): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBFLAGS)

##################################################################
#
# LaTeX stuff
#
##################################################################

GRAPHDATA = graph1.dat
GRAPHPDFS = $(GRAPHDATA:%.dat=%.pdf)
LATEXSRCS = report.tex

# This rule says that 'make pdf' will build report.pdf.
pdfs: report.pdf
# You might prefer a rule like this:
pdfs: DESIGN.pdf WRITEUP.pdf

# This rule defines the dependencies for a particular LaTeX PDF.
# The actions taken depend on the inputs to the PDF.
# Note that a default rule (below) tells make how to create a PDF
# from a corresponding latex file.
report.pdf: $(LATEXSRCS) $(GRAPHPDFS)

# This rule defines how to make graph1.pdf from a program.
# Note that graph1.dat and graph1.pdf are *derived*, since
# they can be recreated exactly by re-running gen_random_data.py
# with the same arguments.
graph1.pdf:
	python3 gen_random_data.py 50 1 100 6502 > graph1.dat
	gnuplot < graph1.plt > graph1.pdf

##################################################################
#
# Generic rules and default rules.
#
##################################################################
# This rule removes the derived files: the executable itself and
# all of the OBJECT files that it can build.
# They can be recreated by running 'make all'.
# It then removes the graph data files and PDFs, since they
# can be recreated by running 'make pdf'.
clean:
	rm -f $(EXECBIN) $(OBJECTS)
	rm -f $(GRAPHDATA) $(GRAPHPDFS)


# This is a default rule for creating a .o file from the corresponding .c file.
%.o : %.c
	$(CC) $(CFLAGS) -c $<

# This is a default rule for creating a .pdf file from the corresponding .tex file.
%.pdf: %.tex
	latexmk -pdf $<
