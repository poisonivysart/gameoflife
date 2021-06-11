#include "board_drawer.h"

void display(int rows, int columns, char* board){
  printf("\n\n\n");
  for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
        printf("\x1b[1;32m %c ", *(board +i*columns + j));
    }
    printf("\n");
  }
}


