#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double getRandomValue(double min, double max);
void begin(int rows, int columns);
char* createBoard(int rows, int columns);
int count(int rows, int columns, int x, int y, char* board);
char* newBoard(int rows, int columns, char* prevBoard);
int isNotEmpty(int rows, int columns, char* board);
compareBoards(int rows,int columns,char* board, char* prevBoard);