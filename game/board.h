#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <SDL2/SDL.h>

// SDL_Event gameEvent;
// SDL_Window *gameWindow;
// SDL_Renderer *gameRenderer;
// SDL_Surface *gameWindowSurface;
// char* gameError;
// int gameWindowWidth, gameWindowHeight;
// int gameWindowXPos, gameWindowYPos;

double getRandomRange(double min, double max);
void display(int rows, int columns, char* board);
void begin(int rows, int columns);
char* create(int rows, int columns);
int count(int rows, int columns, int x, int y, char* board);
char* newBoard(int rows, int columns, char* prevBoard);