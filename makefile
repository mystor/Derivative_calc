CC=gcc
CFLAGS=-lm -std=gnu11 -O0 -Wall

tester: tester.o derivative.o

README.md: proj.org
	$(shell emacs --batch proj.org --funcall=org-md-export-to-markdown --funcall=kill-emacs)
	mv proj.md README.md

.PHONY: clean
clean:
	rm *.o
	rm tester

.PHONY: run
run: tester
	./tester

