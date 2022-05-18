sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic\

mlang: $(objects)
	gcc $(objects) $(flags) -o cobya
	cp cobya mvlna

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	sudo cp ./cobya /usr/local/bin/cobya
	sudo cp ./mvlna /usr/local/bin/mvlna
	make clean

clean:
	rm cobya
	rm mvlna
	rm *.o
	rm *.a
	rm src/*.o

lint:
	clang-tidy src/*.c src/include/*.h
