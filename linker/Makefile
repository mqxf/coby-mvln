sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -Wextra -lm -ldl -fPIC -rdynamic\

cobyl: $(objects)
	gcc $(objects) $(flags) -o cld
	cp cld mld

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	sudo cp ./cld /usr/local/bin/cld
	sudo cp ./mld /usr/local/bin/mld
	make clean

clean:
	-rm src/*.o
	-rm cld
	-rm mld
lint:
	clang-tidy src/*.c src/include/*.h
