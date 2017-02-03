CFLAGS = `pkg-config --libs --cflags gtk+-3.0`
LDFLAGS = -lsqlite3
SRC_FILES = $(wildcard src/*.c)
TEST_FILES = $(filter-out src/main.c, $(SRC_FILES))

default: fernsphex-todo

fernsphex-todo: fernsphex-todo
	gcc $(SRC_FILES) $(CFLAGS) $(LDFLAGS) -o bin/fernsphex-todo

debug:
	-rm -f bin/fernsphex-todo
	gcc -g $(SRC_FILES) $(CFLAGS) $(LDFLAGS) -o bin/fernsphex-todo

clean:
	-rm -f bin/fernsphex-todo tests/test

test:
	gcc -g $(TEST_FILES) tests/*.c $(CFLAGS) $(LDFLAGS) -std=c99 -o tests/test
	tests/test

get-deps:
	sudo apt-get install -y gtk-3-dev libsqlite3-dev
