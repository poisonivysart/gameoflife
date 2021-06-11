#include "board_drawer.h"

/**
 * @param  rows The number of rows on the board
 * @param columns The number of columns on the board
 * @param Board The game board
 * Displays the board on the terminal
 */
void display(int rows, int columns, char* board){
  printf("\n\n\n");
  for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
        printf("\x1b[1;35m %c ", *(board +i*columns + j));
    }
    printf("\n");
  }
}


