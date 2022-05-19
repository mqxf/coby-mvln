sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -Wextra -lm -ldl -fPIC -rdynamic\

mlang: $(objects)
	gcc $(objects) $(flags) -o cas
	cp cas mas

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	sudo cp ./cas /usr/local/bin/cas
	sudo cp ./mas /usr/local/bin/mas
	make clean

clean:
	-rm src/*.o
	-rm cas
	-rm mas

lint:
	clang-tidy src/*.c src/include/*.h
