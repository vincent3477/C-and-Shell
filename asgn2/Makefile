# Name of the program this Makefile is going to build
EXECBIN  = mathlib-test

# Default values for compiling C files
CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra
LIBFLAGS = -lm

# All available .c files are included as SOURCES
SOURCES  = $(wildcard *.c)
# Each .c file has a corresponding .o file
OBJECTS  = $(SOURCES:%.c=%.o)

# These are "phony" targets: they're not real files
.PHONY: all clean

# This is the first actual target in the file.
# That means it's built when 'make' is run without arguments.
all: $(EXECBIN)

# The program depends on *all* of the OBJECTS.
# This means the .o files from *every* .c file in the directory,
# given how we defined $(OBJECTS)
$(EXECBIN): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBFLAGS)

# This rule removes the derived files: the executable itself and
# all of the OBJECT files that it can build.
# They can be recreated by running 'make all'.
clean:
	rm -f $(EXECBIN) $(OBJECTS)

# This is a default rule for creating a .o file from the corresponding .c file.
%.o : %.c
	$(CC) $(CFLAGS) -c $<

