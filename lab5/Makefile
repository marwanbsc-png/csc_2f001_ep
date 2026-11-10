.SUFFIXES:         # remove all the implicit rules (avoid conflicts with our own rules)
.SECONDARY:        # all files are intermediate (keep them, otherwise they are removed)
.PHONY: all clean  # these targets are not files (even if a file named "all" or "clean" exists, the rule is applied)

LDFLAGS=
LIBS=
CFLAGS=-Wall -Werror -g
BIN= tree

all: $(BIN)

$(BIN): node_t.o main.o
	g++ $(LDFLAGS) -o $@ $^ $(LIBS) -std=c++20

%.o: %.cpp
	g++ $(CFLAGS) -o $@ -c $< -std=c++20

node_t.o main.o: NODE_T.h

clean:
	rm -f *.o $(BIN)