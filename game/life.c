#include "life.h"

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

int isNotEmpty(int rows, int columns,char* board){
   for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
        printf("%c", *(board +i*columns + j));
        if(*(board +i*columns + j) == '#'){
          return 1;
        }
    }
  }
  return 0;
}
compareBoards(int rows,int columns,char* board, char* prevBoard){
  if(prevBoard == NULL){
    return 1;
  }
  for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
      if(*(board +i*columns + j) != *(prevBoard +i*columns + j)){
        return 1;
      }
    }
  }
  return 0;
}

void begin(int rows, int columns){

  printf("Starting the Game of Life\n");

  char *board = createBoard(rows, columns); 
  if(board == NULL) return;
  display(rows,columns, board);

  // we are storing the previous board here to compare the new board with
  char* prevBoard = (char*)calloc(rows*columns, sizeof(char));

  // while all the cells are not dead and the table is not repeated in every iterations (where the progressions stops)
  // execute the loop
  while(isNotEmpty(rows,columns, board) && compareBoards(rows,columns,board, prevBoard)){
    char* newBoard = nextBoard(rows, columns, board);
    if(newBoard == NULL){
      printf("Error with creating of a new board.\n");
      return;
    }
    // setting the prevBoard pointer to the old one
    prevBoard = board;
    // freeing the old board, nno need for that memory anymore
    free(board);
    // setting the board pointer to point to the newly create board
    board = newBoard;
    // displaying the updated board
    display(rows, columns, board); // show the updated board
    // intervals between tables to create a smooth watching experience of the cell progression
    usleep(100000); 
  }
}


int count(int rows, int columns, int x, int y, char* board){
  int counter = 0;
  int cell = x*columns  + y;
  for(int i =  -1; i<= 1;i++){
    for(int j =  -1; j<= 1;j++){
      char c = *(board + cell +(i*columns) + j);
      if(c == '#') counter++;

    }
  }
  return counter;
}


// to randomize the placement of the hashes on the initial table, so that
// the game of life could start
// a standard random value expression was used, nothing too special
double getRandomValue(double min, double max){
  return ((double)rand()/RAND_MAX)*(max-min)+min;
}

char* createBoard(int rows, int columns){
  char* board = (char*)calloc(rows*columns, sizeof(char));
  if(board== NULL){
    printf("Memory allocation error\n");
    return NULL;
  }
  for(int i = 1; i < rows-1; i++){
    for(int j =1; j < columns-1; j++){
      // checks if the randm value is below 4, basically 40%, then the cell is alive
      if(getRandomValue(0.0,10.0) <= 4) *(board +i*columns + j) = '#';
      // otherwise the cell is dead, most of the time
      else *(board +i*columns + j) = '.'; 
    }
  }
  return board;
}
