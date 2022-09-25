CC = g++
CFLAGS = -std=c++11

build: sudoku

run:
	rm -f output.txt
	touch output.txt
	./sudoku $(INPUT_FILE)

sudoku: main.o sudokuGrid.o
	$(CC) $(CFLAGS) main.o sudokuGrid.o -o sudoku

main.o: main.cpp sudokuGrid.o
	$(CC) $(CFLAGS) -c main.cpp

sudokuGrid.o: sudokuGrid.cpp
	$(CC) $(CFLAGS) -c sudokuGrid.cpp

clean:
	rm -f sudoku
	rm -f *.o
	rm -f output.txt