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

#define ROWS 7
#define COLUMNS 8

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int count(int rows, int columns, int x, int y, char* board);
char* nextBoard(int rows, int columns, char* prevBoard);
char* create(int rows, int columns);
double getRandomRange(double min, double max);
void display(int rows, int columns, char* board);

void testNextBoard(){
  // nextBoard also shouldn't return a NULL
  char* prevBoard = create(ROWS, COLUMNS);
  CU_ASSERT(nextBoard(ROWS, COLUMNS, prevBoard) != NULL);
}

void testCreate(){
  // here we will check the creation of the game of life board. Let's see if it returns a real pointer or NULL.
  CU_ASSERT(create(ROWS, COLUMNS) != NULL);
}

void testGetRandomRange(){
  // Here we need to check the values that the function returns, they should be truthful
  // these should be between 0 and 1
  // We have many tests to test the randomizer
  CU_ASSERT(getRandomRange(0.0,1.0) >= 0.0 && getRandomRange(0.0,1.0) <= 1.0);
  CU_ASSERT(getRandomRange(0.0,1.0) >= 0.0 && getRandomRange(0.0,1.0) <= 1.0);
  CU_ASSERT(getRandomRange(0.0,1.0) >= 0.0 && getRandomRange(0.0,1.0) <= 1.0);
  CU_ASSERT(getRandomRange(0.0,1.0) >= 0.0 && getRandomRange(0.0,1.0) <= 1.0);
  CU_ASSERT(getRandomRange(0.0,1.0) >= 0.0 && getRandomRange(0.0,1.0) <= 1.0);
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
  // add testGetRandomRange to suite1
  if ((NULL == CU_add_test(pSuite1,"\n\n……… Testing getRandomRange function……..\n\n", testGetRandomRange))){
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


  
  CU_basic_run_tests();// OUTPUT to the screen

  CU_cleanup_registry();//Cleaning the Registry
  return CU_get_error();


  return 0;
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


double getRandomRange(double min, double max){
  printf("%f\n",((double)rand()/RAND_MAX)*(max-min)+min);
  return ((double)rand()/RAND_MAX)*(max-min)+min;
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


int count(int rows, int columns, int x, int y, char* board){
  int count = 0;
  int pivot = x*columns  + y; //?

  for(int i =  -1; i<= 1;i++){
    for(int j =  -1; j<= 1;j++){
      
      char c = *(board + pivot +(i*columns) + j);

      if(c == '#') count++;

    }
  }
  return count-1; // we shouldn't consider our own element
}

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