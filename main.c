#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game/life.h"

/**
 * @file doxygen_c.h
 * @author Sarkhan
 */

/** \mainpage Game of Life
 * The purpose of the project was to build a cellular automaton defined by the English mathematician John Conway in 1970. The Game of Life contains a universe inside where cells become alive and die. Of course, there are some rules to it.  And there were some steps to follow during the building of the application, which will be discussed now. P.S Some steps were combined and merged and modified depending on the circumstances and will be mentioned in the following pages.
 * \section Rules
 * - A dead cell at time t becomes alive at time t + 1 if and only if it has exactly
 * - 3 living cells in its vicinity.
 * - A living cell at time t remains alive at time t + 1 if and only if it has exactly 2
 * - 3 living cells in its vicinity, otherwise it dies.
 * - All other cells dies
 * - The neighborhood used is the 8-neighborhood: for a given cell, its neighbors are the 8 cells that surround it
 * \section Technologies
 * CMake, CUnit and Github Actions were used for further improvement of the application. 
 * - CMake is cross-platform free and open-source software for build automation, testing, packaging and installation of software by using a compiler-independent method. 
 * - CUnit helps to test the code and find the vulnerabilities
 * - Github Actions helps with continuous integration, configuring, building the CMake, and testing the application as soon as the file is pushed to the github repository
 */


/// This is the main function which gets executed first
int main(){

  srand(time(NULL));
  int rows, columns, choice;
  printf("Choose one of the below:\n");
  printf("(1) Input my rows and columns with randomized table\n");
  printf("(2) Draw a random table without inputting anything\n");
  printf("(3) Draw a decending glider\n");
  printf("Your choice: ");
  scanf("%d",&choice);

  switch(choice){
    case 1:
      printf("Enter the number of rows and columns respectively (space between): ");
      scanf("%d%d", &rows, &columns);
      begin(rows+2,columns+2);
      break;
    case 2:
      begin(12,12);
      break;
    case 3:
      glider();
      break;
  }
  

  // we add those 2 extra columsn and rows for the wrapper around the board. 
  // because during calculations it will be needed, so that they don't go
  // out of border and we don't get an error
  
  
  return 0;
}