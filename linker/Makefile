sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic\

mlang: $(objects)
	gcc $(objects) $(flags) -o cobyl
	cp cobyl mvlnl

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	sudo cp ./cobyl /usr/local/bin/cobyl
	sudo cp ./mvlnl /usr/local/bin/mvlnl
	make clean

clean:
	rm cobyl
	rm mvlnl
	rm *.o
	rm *.a
	rm src/*.o

lint:
	clang-tidy src/*.c src/include/*.h
