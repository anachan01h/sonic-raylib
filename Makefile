bin/sonic-demo: bin/ src/main.c
	gcc src/main.c -o bin/sonic-demo -lraylib -lm

bin/:
	mkdir bin

run: bin/sonic-demo
	./bin/sonic-demo

.PHONY: clean
clean:
	rm -rf bin
