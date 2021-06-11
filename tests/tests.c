#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <CUnit/CUnit.h>	  // ASSERT macros for use in test cases, and includes other framework headers.
#include <CUnit/CUError.h>	// Error handing functions and data types. Included automatically by CUnit.h.
#include <CUnit/TestDB.h>	  // Data type definitions and manipulation functions for the test registry, suites, and tests. Included automatically by CUnit.h.
#include <CUnit/TestRun.h>	// Data type definitions and functions for running tests and retrieving results. Included automatically by CUnit.h.
#include <CUnit/Automated.h>// Automated interface with xml output.
#include <CUnit/Basic.h>	  // Basic interface with non-interactive output to stdout.
#include <CUnit/Console.h>	// Interactive console interface.

// I define the default rows and columns here
#define ROWS 7
#define COLUMNS 8

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int count(int rows, int columns, int x, int y, char* board);
char* nextBoard(int rows, int columns, char* prevBoard);
char* createBoard(int rows, int columns);
double getRandomValue(double min, double max);
void display(int rows, int columns, char* board);
int compareBoards(int rows,int columns,char* board, char* prevBoard);
int isNotEmpty(int rows, int columns,char* board);

void testNextBoard(){
  // nextBoard also shouldn't return a NULL
  char* prevBoard = createBoard(ROWS, COLUMNS);
  CU_ASSERT(nextBoard(ROWS, COLUMNS, prevBoard) != NULL);
}

void testCreate(){
  // here we will check the creation of the game of life board. Let's see if it returns a real pointer or NULL.
  CU_ASSERT(createBoard(ROWS, COLUMNS) != NULL);
}

void testIsNotEmpty(){
  char* board1 = createBoard(ROWS, COLUMNS);
  CU_ASSERT(1==isNotEmpty(ROWS, COLUMNS, board1));
  char* board2 = (char*)calloc(ROWS*COLUMNS, sizeof(char));
  CU_ASSERT(0 == isNotEmpty(ROWS,COLUMNS,board2));
}

void testCompareBoards(){
  char* board1 = (char*)calloc(ROWS*COLUMNS, sizeof(char));
  char* board2 = (char*)calloc(ROWS*COLUMNS, sizeof(char));
  CU_ASSERT(compareBoards(ROWS,COLUMNS,board1, board2) == 0);
}

void testGetRandomValue(){
  // Here we need to check the values that the function returns, they should be truthful
  // these should be between 0 and 1
  // We have many tests to test the randomizer
  CU_ASSERT(getRandomValue(0.0,1.0) >= 0.0 && getRandomValue(0.0,1.0) <= 1.0);
  CU_ASSERT(getRandomValue(0.0,1.0) >= 0.0 && getRandomValue(0.0,1.0) <= 1.0);
  CU_ASSERT(getRandomValue(0.0,1.0) >= 0.0 && getRandomValue(0.0,1.0) <= 1.0);
  CU_ASSERT(getRandomValue(0.0,1.0) >= 0.0 && getRandomValue(0.0,1.0) <= 1.0);
  CU_ASSERT(getRandomValue(0.0,1.0) >= 0.0 && getRandomValue(0.0,1.0) <= 1.0);
}

void testCount(){
  //basic setup for the test
  char* board = (char*)calloc(ROWS*COLUMNS, sizeof(char));
  for(int i = 1; i < ROWS-1; i++){
    for(int j =1; j < COLUMNS-1; j++){
        *(board +i*COLUMNS + j) = '#';
    }
  }
  
  // here one of the middle elements should have a count of 8, let's check
  CU_ASSERT(8 == count(ROWS, COLUMNS, 3,3,board));
  
}

int main(){

  CU_pSuite pSuite1 = NULL;
  // Initialize CUnit test registry
  if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
  // Add suite1 to registry
  pSuite1 = CU_add_suite("Basic_Test_Suite1", init_suite, clean_suite);
  if (NULL == pSuite1) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // add testCount to suite1
  if ((NULL == CU_add_test(pSuite1,"\n\n……… Testing count function……..\n\n", testCount))){
    CU_cleanup_registry();
    return CU_get_error();
  }
  // add testgetRandomValue to suite1
  if ((NULL == CU_add_test(pSuite1,"\n\n……… Testing getRandomValue function……..\n\n", testGetRandomValue))){
    CU_cleanup_registry();
    return CU_get_error();
  }
// add testCreate to suite1
  if ((NULL == CU_add_test(pSuite1,"\n\n……… Testing create function……..\n\n", testCreate))){
    CU_cleanup_registry();
    return CU_get_error();
  }
// add testNextBoard to suite1
  if ((NULL == CU_add_test(pSuite1,"\n\n……… Testing nextBoard function……..\n\n", testNextBoard))){
    CU_cleanup_registry();
    return CU_get_error();
  }
// add testIsNotEmpty to suite1
  if ((NULL == CU_add_test(pSuite1,"\n\n……… Testing isNotEmpty function……..\n\n", testIsNotEmpty))){
    CU_cleanup_registry();
    return CU_get_error();
  }
// add testCompareBoards to suite1
  if ((NULL == CU_add_test(pSuite1,"\n\n……… Testing compareBoards function……..\n\n", testCompareBoards))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  
  CU_basic_run_tests();// OUTPUT to the screen

  CU_cleanup_registry();//Cleaning the Registry
  return CU_get_error();


  return 0;
}

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
      if(cell == '#') c--; //we dont count ourselves
      // by default we assign the original cell to the new one
      *(newBoard + i*columns+j) = cell;

      // here we start checking how many surrounding cells are alive
      // if it's 2 or 3 and the cell is alive itself, it stays alive
      if((c == 2 || c == 3) && cell == '#'){
        *(newBoard + i*columns+j) = '#';
      // if it's exactly 3 and the cell is dead, it becomes alive
      }else if(c == 3 && cell == '.'){
        *(newBoard + i*columns+j) = '#';
      // in all other cases it is dead or becomes dead
      }else{
        *(newBoard + i*columns+j) = '.';
      }
    }
  }
  return newBoard;

}





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

// count the number of live cells around the current cell
int count(int rows, int columns, int x, int y, char* board){
  int counter = 0; // a standard counter
  int cell = x*columns  + y; // we locate and take our current cell
  // the loop with range [-1,1] to find the cells around it, 8 overall
  for(int i =  -1; i<= 1;i++){
    for(int j =  -1; j<= 1;j++){
      char c = *(board + cell +(i*columns) + j);
      if(c == '#') counter++; // if the cell is alive, then add to the counter

    }
  }
  return counter;
}

double getRandomValue(double min, double max){
  return ((double)rand()/RAND_MAX)*(max-min)+min;
}


// initial creation of a board with random dead and live cells
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

int compareBoards(int rows,int columns,char* board, char* prevBoard){
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
  printf("The cells in the table liked their positions and wouldn't change anymore. The Game of Life has come to an end!\n");
  return 0; 
  
}

int isNotEmpty(int rows, int columns,char* board){
   for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
        if(*(board +i*columns + j) == '#'){ 
          return 1;
        }
    }
  }
  printf("After a huge war, all cells are dead. The Game of Life has come to an end!\n");
  return 0; 
}

void display(int rows, int columns, char* board){
  printf("\n\n\n");
  for(int i = 1; i < rows-1; i++){
    for(int j = 1; j < columns-1; j++){
        printf("\x1b[1;32m %c ", *(board +i*columns + j));
    }
    printf("\n");
  }
}