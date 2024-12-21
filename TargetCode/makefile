.SUFFIXES:

.PHONY: build test clean

# Default rule for building the translator
build:
	bison -d parser.y                  # Generate parser.tab.c and parser.tab.h
	flex -o lex.yy.c lexer.l           # Generate lex.yy.c
	gcc -o translator lex.yy.c parser.tab.c symbol_table.c   # Compile into the translator

# Rule for running the translator on a test case
test: build
	./translator < testcase.f15

# Clean up generated files
clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c translator
