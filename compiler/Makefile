sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -Wextra -lm -ldl -fPIC -rdynamic

cobyc: $(objects)
	gcc $(objects) $(flags) -o cobyc
	cp cobyc mvc

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	sudo cp ./cobyc /usr/local/bin/cobyc
	sudo cp ./mvc /usr/local/bin/mvc
	make clean

clean:
	-rm src/*.o
	-rm cobyc
	-rm mvc

lint:
	clang-tidy src/*.c src/include/*.h
