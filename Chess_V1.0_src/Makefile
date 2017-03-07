TARGET = Chessence

CC = gcc
CFLAGS = -ansi -Wall -g
#LFLAGS = -ansi -Wall

SOURCE = src/AI.c src/Chessence.c src/ChessIO.c src/FileIO.c src/InitializeBoard.c src/Move.c src/MoveList.c src/PrintBoard.c

OBJECT = src/AI.o src/Chessence.o src/ChessIO.o src/FileIO.o src/InitializeBoard.o src/Move.o src/MoveList.o src/PrintBoard.o

###################################################

bin/$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o bin/$(TARGET) 

src/%.o:  %.c
	$(CC) $(CFLAGS) -c -o "$<" "$@"


clean:
	rm -f *~ $(OBJECT) bin/$(TARGET) bin/*.txt 

tar:
	tar -czvf Chess_Alpha_src.tar.gz ../Chess_Alpha_src 	


