#include "board.h"

char* nextBoard(int rows, int columns, char* prevBoard){
  char* new = (char*)calloc(rows*columns, sizeof(char));
  if(new == NULL) return NULL;

  for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
      
      int c = count(rows, columns, i, j, prevBoard);
      char cell = *(prevBoard + i*columns+j);
      if(cell == '#') c--; //we dont count ourselves
      *(new + i*columns+j) = cell;

      if((c == 2 || c == 3) && cell == '#'){
        *(new + i*columns+j) = '#';
      }else if(c == 3 && cell == '.'){
        *(new + i*columns+j) = '#';
      }else{
        *(new + i*columns+j) = '.';
      }
    }
  }
  return new;

}

void begin(int rows, int columns){
  // gameWindow = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	// if (gameWindow == NULL)
	// {
	// 	gameError = "SDL Failed to create window!";
	// 	exit(-1);
	// }

	// gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	// if (gameRenderer == NULL)
	// {
	// 	gameError = "SDL Failed to create renderer!";
	// 	exit(-1);
	// }

  // SDL_SetRenderDrawBlendMode(gameRenderer, SDL_BLENDMODE_BLEND);
	// gameWindowSurface = SDL_GetWindowSurface(gameWindow);
  // SDL_GetWindowSize(gameWindow, &gameWindowWidth, &gameWindowHeight);

  // gridWidth = 128;
	// gridHeight = 72;

  puts("Drawing...");
  char *board = create(rows, columns);
  if(board == NULL) return;
  display(rows,columns, board);

  while(1){
    char* newBoard = nextBoard(rows, columns, board);
    if(newBoard == NULL){
      printf("Error with creating of a new board.\n");
      return;
    }
    free(board);
    board = newBoard;
    display(rows, columns, board);
    usleep(1000000);
  }
}


int count(int rows, int columns, int x, int y, char* board){
  int count = 0;
  int pivot = x*columns  + y; //?

  for(int i =  -1; i<= 1;i++){
    for(int j =  -1; j<= 1;j++){
      
      char c = *(board + pivot +(i*columns) + j);

      if(c == '#') count++;

    }
  }
  return count;
}

double getRandomRange(double min, double max){
  printf("%f\n",((double)rand()/RAND_MAX)*(max-min)+min);
  return ((double)rand()/RAND_MAX)*(max-min)+min;
}


void display(int rows, int columns, char* board){
  // printf("\033[H\033\[J"); //to clean the screen
  printf("\n\n\n\n\n");
  for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
      printf("%c ", *(board +i*columns + j));
    }
    printf("\n");
  }
}




char* create(int rows, int columns){
  char* board = (char*)calloc(rows*columns, sizeof(char));
  if(board== NULL){
    printf("No memory exists\n");
    return NULL;
  }
  for(int i = 1; i < rows-1; i++){
    for(int j =1; j < columns-1; j++){
      if(getRandomRange(0.0,1.0) <= 0.35){
        *(board +i*columns + j) = '#';
      }else{
        *(board +i*columns + j) = '.';
      }
      
    }
  }
  return board;
}
