CC=gcc
CFLAGS=-std=gnu11 -O0 -Wall

tester: derivative.o test.o

clean:
	rm *.o

readme: # Please ignore this horrible hack
	$(shell emacs --batch proj.org --funcall=org-md-export-to-markdown --funcall=kill-emacs)
	mv proj.md README.md
