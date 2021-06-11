#include "life.h"

/**
 * @file doxygen_c.h
 * @author Sarkhan
 * @brief File containing example of doxygen usage for quick reference.
 *
 */

/**
 * @param  rows The number of rows on the board
 * @param columns The number of columns on the board
 * @param prevBoard The old board before updates to create a new one
 * Creates a new board out of the old one. 
 */
char* nextBoard(int rows, int columns, char* prevBoard){
  // standard creation of the new board and the filling it with cells
  char* newBoard = (char*)calloc(rows*columns, sizeof(char));
  if(newBoard == NULL) return NULL;

  for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
      // we assign a cell to be dead or alive in accordance with its surrounding cells    
      int c = count(rows, columns, i, j, prevBoard);
      //  our original cell
      char cell = *(prevBoard + i*columns+j);
      // if the cell itself is alive, then we subtract one to not mess with out calculation
      if(cell == 'O') c--; //we dont count ourselves
      // by default we assign the original cell to the new one
      *(newBoard + i*columns+j) = cell;

      // here we start checking how many surrounding cells are alive
      // if it's 2 or 3 and the cell is alive itself, it stays alive
      if((c == 2 || c == 3) && cell == 'O'){
        *(newBoard + i*columns+j) = 'O';
      // if it's exactly 3 and the cell is dead, it becomes alive
      }else if(c == 3 && cell == ' '){
        *(newBoard + i*columns+j) = 'O';
      // in all other cases it is dead or becomes dead
      }else{
        *(newBoard + i*columns+j) = ' ';
      }
    }
  }
  return newBoard;

}
/**
 * @param  rows The number of rows on the board
 * @param columns The number of columns on the board
 * @param board The board of the game
 * A function to check whether the table is filled with only dead cells or not
 */
int isNotEmpty(int rows, int columns,char* board){
   for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
        if(*(board +i*columns + j) == 'O'){ // if there's at least one live cell, we return 1
          return 1;
        }
    }
  }
  printf("After a huge war, all cells are dead. The Game of Life has come to an end!\n");
  return 0; // otherwise there are no live cells
}

/**
 * @param  rows The number of rows on the board
 * @param columns The number of columns on the board
 * @param board The board of the game
 * @param prevBoard The previous board of the game, before updates
 * Compares 2 tables, previous and current and if they are the same
 * returns 0 to stop the while loop in begin function
 */
int compareBoards(int rows,int columns,char* board, char* prevBoard){
  // in the first iteration the prevBoard will be null and we don't want it
  // to mess our code. So we have this condition
  if(prevBoard == NULL){
    return 1;
  }
  for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
      // if the characters are not the same then return 1, because the tables are not the same of course
      if(*(board +i*columns + j) != *(prevBoard +i*columns + j)){ 
        return 1;
      }
    }
  }
  printf("The cells in the table liked their positions and wouldn't change anymore. The Game of Life has come to an end!\n");
  return 0; // otherwise the tables are the same and return 0 to stop the loop
  
}
/**
 * @param  rows The number of rows on the board
 * @param columns The number of columns on the board
 * Starts the game
 */
void begin(int rows, int columns){

  printf("Starting the Game of Life\n");

  // we create a new board with random dead and alive cells
  char *board = createBoard(rows, columns); 
  if(board == NULL) return; // check if the board is created or not
  display(rows,columns, board); // display the initial board

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

/**
 * @param  rows The number of rows on the board
 * @param columns The number of columns on the board
 * @param x The x coordinate on the table
 * @param y The y coordinate on the table
 * @param board The board itself
 * Counts the number of live cells around the current cell
 * 
 */
int count(int rows, int columns, int x, int y, char* board){
  int counter = 0; // a standard counter
  int cell = x*columns  + y; // we locate and take our current cell
  // the loop with range [-1,1] to find the cells around it, 8 overall
  for(int i =  -1; i<= 1;i++){
    for(int j =  -1; j<= 1;j++){
      char c = *(board + cell +(i*columns) + j);
      if(c == 'O') counter++; // if the cell is alive, then add to the counter

    }
  }
  return counter;
}

/**
 * @param  min Lower bound of the interval
 * @param max Upper bound of the interval
 * To randomize the placement of the hashes on the initial table, so that the game of life could start 
 * A standard random value expression was used, nothing too special
 */
double getRandomValue(double min, double max){
  return ((double)rand()/RAND_MAX)*(max-min)+min;
}

/**
 * @param  rows The number of rows on the board
 * @param columns The number of columns on the board
 * 
 */
// Creates a board with random dead and living cells
char* createBoard(int rows, int columns){
  char* board = (char*)calloc(rows*columns, sizeof(char));
  if(board== NULL){
    printf("Memory allocation error\n");
    return NULL;
  }
  for(int i = 1; i < rows-1; i++){
    for(int j =1; j < columns-1; j++){
      // checks if the randm value is below 4, basically 40%, then the cell is alive
      if(getRandomValue(0.0,10.0) <= 4) *(board +i*columns + j) = 'O';
      // otherwise the cell is dead, most of the time
      else *(board +i*columns + j) = ' '; 
    }
  }
  return board;
}

/**
 * A function to draw an interesting pattern on the board, namely a glider animation decending from top left to bottom right
 */
void glider(){
  printf("Starting the Game of Life\n");

  int rows = 9, columns = 9;
  // we create a new board with random dead and alive cells
  // char *board = createBoard(rows, columns); 
  char* board = (char*)calloc(rows*columns, sizeof(char));
  if(board == NULL) return; // check if the board is created or not
  for(int i = 1; i < rows-1; i++){
    for(int j =1; j < columns-1; j++){
      *(board +i*columns + j) = ' '; 
    }
  }

  *(board + 13) = 'O';
  *(board + 23) = 'O';
  *(board + 30) = 'O';
  *(board + 31) = 'O';
  *(board + 32) = 'O';

  display(rows,columns, board); // display the initial board

  char* prevBoard = (char*)calloc(rows*columns, sizeof(char));
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
    usleep(1000000); 
  }
}