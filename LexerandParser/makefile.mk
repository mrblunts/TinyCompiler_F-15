.SUFFIXES:

.PHONY: build test clean

# Default rule for building the translator
build:
	bison parser.y
	flex lexer.l                # Generate lex.yy.c
	gcc -o output lex.yy.c parser.tab.c main.c  # Compile the output executable

# Rule for running the translator on a test case
test: build
	@echo "Running the translator on a test case..."
	./output < testcase          # Replace 'testcase' with your actual test file

# Clean up generated files
clean:
	rm -f lex.yy.c parser.tab.c y.tab.c y.tab.h output # you may remove the generated files for clean up
	