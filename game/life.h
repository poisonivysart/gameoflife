#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//! Starts the game
void begin(int rows, int columns);
//! Returns a random double between min and max given by the application
double getRandomValue(double min, double max);
//! Creates a board at the start
char* createBoard(int rows, int columns);

//! Counts the number of live cells around the current given cell
int count(int rows, int columns, int x, int y, char* board);

//! creates a new board to fill and update with the progression from the previous board 
char* newBoard(int rows, int columns, char* prevBoard);

//! Checks whether the board has only dead cells or there's at least one live cell
int isNotEmpty(int rows, int columns, char* board);

//! Compares two boards and whether they are the same or not
int compareBoards(int rows,int columns,char* board, char* prevBoard);
void glider();