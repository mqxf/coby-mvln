sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic\

cobyc: $(objects)
	gcc $(objects) $(flags) -o cobyc
	cp cobyc mvlnc

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	sudo cp ./cobyc /usr/local/bin/cobyc
	sudo cp ./mvlnc /usr/local/bin/mvlnc
	make clean

clean:
	rm src/*.o
	rm cobyc
	rm mvlnc

lint:
	clang-tidy src/*.c src/include/*.h
