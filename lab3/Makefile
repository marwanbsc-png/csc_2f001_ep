.SUFFIXES:         # remove all the implicit rules (avoid conflicts with our own rules)
.SECONDARY:        # all files are intermediate (keep them, otherwise they are removed)
.PHONY: all clean  # these targets are not files (even if a file named "all" or "clean" exists, the rule is applied)

LDFLAGS=
LIBS=
CFLAGS=-Wall -Werror -g
BIN=army-pokemon army-zombie

all: $(BIN)

army-%: main.o monster.o army-%.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBS)

main.o monster.o: monster.h army.h macro.h

army.o: monster.o army.h
	gcc $(CFLAGS) -o $@ -c army-pokemon.c

%.o: %.c 
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(BIN) *.o *~ 
