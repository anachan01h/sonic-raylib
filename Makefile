bin/sonic-demo: bin/ src/main.c src/sonic.c inc/sonic.h
	gcc src/main.c src/sonic.c -o bin/sonic-demo -lraylib -lm -L../inc

bin/:
	mkdir bin

run: bin/sonic-demo
	./bin/sonic-demo

.PHONY: clean
clean:
	rm -rf bin
