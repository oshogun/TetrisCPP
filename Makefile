
CC=g++
LIBS= -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
SRCDIR=src
INCLUDEDIR=include
all:
	$(CC) $(SRCDIR)/*.cpp -O3 -I$(INCLUDEDIR) $(LIBS) -o Tetris -std=c++17

clean:
	rm Tetris

run:
	./Tetris
