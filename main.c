// #include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 5
#define COLUMNS 10

// // for initializing and sutdown functions
// #include <SDL2/SDL.h>
 
// // for rendering images and graphics on screen
// #include <SDL2/SDL_image.h>
 
// // for using SDL_Delay() functions
// #include <SDL2/SDL_timer.h>

// int sdl_setup(){
//   if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//         printf("error initializing SDL: %s\n", SDL_GetError());
//   }
//   SDL_Window* win = SDL_CreateWindow("GAME OF LIFE",
//                                        SDL_WINDOWPOS_CENTERED,
//                                        SDL_WINDOWPOS_CENTERED,
//                                        1000, 1000, 0);
    // while (1);
// }
int main(){
 // retutns zero on success else non-zero
    // SDL_SetMainReady();
    

  srand(time(NULL));
  begin(ROWS+2,COLUMNS+2);
  
  return 0;
}