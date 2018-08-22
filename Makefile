
CC=g++
LIBS=-fopenmp -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
SRCDIR=src
INCLUDEDIR=include
all:
	$(CC) $(SRCDIR)/*.cpp -I$(INCLUDEDIR) $(LIBS) -o Tetris -std=c++17

clean:
	rm Tetris

run:
	./Tetris
