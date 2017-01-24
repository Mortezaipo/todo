CFLAGS = `pkg-config --libs --cflags gtk+-3.0`
LDFLAGS = -lsqlite3

default: fernsphex-todo

fernsphex-todo: fernsphex-todo
	gcc src/* $(CFLAGS) $(LDFLAGS) -o bin/fernsphex-todo

clean:
	-rm -f bin/fernsphex-todo
