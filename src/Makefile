CC   = g++
LIBS = -lSDL2 -lSDL2_gfx
PROG = VirusGame
FLAGS = -std=c++17 -Wall -Wextra -pedantic
HEADERS  := $(wildcard *.h)

all: 	$(PROG)

%: %.cpp $(HEADERS)
	$(CC) $(FLAGS) -o $@ $< $(LIBS)

clean: 
	rm -f $(PROG)
