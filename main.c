#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @file doxygen_c.h
 * @author My Self
 * @date 9 Sep 2012
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */


int main(){

  srand(time(NULL));
  int rows, columns;
  printf("Enter the number of rows and columns respectively (space between): ");
  scanf("%d%d", &rows, &columns);

  // we add those 2 extra columsn and rows for the wrapper around the board. 
  // because during calculations it will be needed, so that they don't go
  // out of border and we don't get an error
  begin(rows+2,columns+2);
  
  return 0;
}