CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGS_E = `pkg-config --libs gtk+-3.0`
LDFLAGS = -lsqlite3
SRC_FILES = $(wildcard src/*.c)
TEST_FILES = $(filter-out src/main.c, $(SRC_FILES))

default: todo

todo: todo
	gcc $(SRC_FILES) $(CFLAGS) $(LDFLAGS) -o bin/todo $(CFLAGS_E)

debug:
	-rm -f bin/todo
	gcc -g $(SRC_FILES) $(CFLAGS) $(LDFLAGS) -o bin/todo $(CFLAGS_E)

clean:
	-rm -f bin/todo tests/test

test:
	gcc $(TEST_FILES) tests/*.c $(CFLAGS) $(LDFLAGS) -std=c99 -o tests/test $(CFLAGS_E)
	tests/test

get-deps:
	sudo apt-get install -y gtk-3-dev libsqlite3-dev
