all: main.out

clean:
	rm -f *.out

main.out: ./src/*.c
	cc ./src/*.c -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -Wall -pedantic -o main.out

run: main.out
	./main.out

leaks: main.out
	leaks -atExit -- ./main.out


.PHONY: all, clean, run, leaks

