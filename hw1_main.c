//Kevin Dugas
//CS 201 - Rivas
// Homework 1 - Maze Traversal
// April 13, 2020

//This file contains the main() function.

#include "hw1.h" 

int main(int argc, char * argv[]){

   // Create and allocate memory for struct params object
   struct params * maze = (struct params *) malloc(sizeof(struct params));
   
   //If incorrect number of arguments, output format to stdout 
   if(argc != 2){
      printf("Format: %s [FILENAME]\n", argv[0]);
      return 0;
   }

   if(!get_params(argv[1], maze))
      return 0;
   if(!build_maze(argv[1], maze))
      return 0;
   traverse_maze(maze);

   delete_maze(maze); 
   return 0;
}

