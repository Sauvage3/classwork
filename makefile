.PHONY: clean run compile clone

default: run

compile pipeDemo : 12-06.o
	@gcc -o pipeDemo 12-06.o -w

main.o: main.c
	@gcc -c 12-06.c -w


run: pipeDemo
	@./pipeDemo

clean:
	@rm -f *.o
	@rm -f pipeDemo


clone:
	@bash test.sh
