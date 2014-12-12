CC=gcc
CFLAGS=-std=gnu11 -O0 -Wall
LIBS=-lm

main: main.o parser.o derivative.o
	$(CC) $(LIBS) $^ -o $@

README.md: proj.org
	$(shell emacs --batch proj.org --funcall=org-md-export-to-markdown --funcall=kill-emacs)
	mv proj.md README.md

.PHONY: clean
clean:
	rm *.o
	rm main

.PHONY: run
run: main
	./main

