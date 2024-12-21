.SUFFIXES:

.PHONY: build test clean

# Default rule for building the translator
build:
	flex lexer.l                # Generate lex.yy.c
	gcc -o output lex.yy.c main.c  # Compile the output executable

# Rule for running the translator on a test case
test: build
	@echo "Running the translator on a test case..."
	./output < testcase          # Replace 'testcase' with your actual test file

# Clean up generated files
clean:
	rm -f lex.yy.c output
