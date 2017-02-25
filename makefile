all:	
	gcc *.c -g -lm -lgsl -lgslcblas -o parser

clean:
	rm parser
