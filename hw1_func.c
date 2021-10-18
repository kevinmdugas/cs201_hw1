//Kevin Dugas
//CS 201 - Rivas
// Homework 1 - Maze Traversal
// April 13, 2020

//This file contains the implementation of the functions whose prototypes are in the file "hw1.h"

#include "hw1.h"

/*
get_params() opens the file specified in argv[1] passed in from main and reads
the first three lines into a temporary char array before parsing each line into
integer members of the passed in params array. It returns an int to main signifying
success or failure; if a 0 is passed back, the file passed in was invalid. If a 1 is 
passed, the function operation was successful.
*/
int get_params(char file[], struct params *maze){
   FILE *ptr = fopen(file, "r");       //Pointer to the passed in file for reading
   char text[MAXLINE];                 //Temporary char array for storing read text from file
   char *temp;                         //Pointer to the remaining char string after converting to int

   //File can't be opened
   if(!ptr){
      printf("Invalid Argument\n");
      return 0;
   }

   //Read from argv[1] and parse maze dimenstions  
   fgets(text, MAXLINE, ptr);
   maze->col = strtol(text, &temp, 10);
   maze->row = strtol(temp+1, NULL, 10);
   //Add space for '\n' & '\0'
   maze->col += 2;

   //Get entry coordinates
   fgets(text, MAXLINE, ptr);
   maze->x_entry = strtol(text, &temp, 10);
   maze->y_entry = strtol(temp+1, NULL, 10);

   //Get exit coordinates
   fgets(text, MAXLINE, ptr);
   maze->x_exit = strtol(text, &temp, 10);
   maze->y_exit = strtol(temp+1, NULL, 10);

   //Print maze parameters to std out
   printf("\n----------------------------");
   printf("\n| Maze Dimensions: [%d,%d] \n", maze->col, maze->row);
   printf("| Entry Point: (%d,%d) \n| Exit Point: (%d,%d) \n", maze->x_entry, maze->y_entry, maze->x_exit, maze->y_exit);
   printf("----------------------------\n");

   fclose(ptr);
   
   return 1;
}



/*
build_maze() uses the newly populated maze dimensions, entry coordinates, and exit
coordinates in the params struct to first construct a dynamically allocated 2d array
to store the maze map. It then reads in each line of the maze from the passed in argv[1]
file into each row of the maze map before printing the maze back to stdout. Like in
get_params(), the function returns a zero if the file was invalid and a one if the 
operation was successful.
*/
int build_maze(char file[], struct params *maze){
   FILE *ptr = fopen(file, "r");                               //Pointer to the passed in file
   char *temp = (char *) malloc(sizeof(char) * (maze->col));   //Dynamically allocated temporary array used to copy from file into map

   //If file cannot be opened
   if(!ptr){
      printf("\nInvalid File\n");
      temp = NULL;
      free(temp);
      return 0;
   }

   //Allocate 2D array
   maze->map = (char **) malloc(sizeof(char*) * (maze->row));
   for(int i = 0; i < maze->row; ++i)
      maze->map[i] = (char *) malloc(sizeof(char) * (maze->col));

   //Read first three lines before maze
   for(int i = 0; i < 3; ++i)
      fgets(temp, MAXLINE, ptr);

   //Read and populate maze
   for(int i = 0; i < maze->row; ++i){
      fgets(temp, maze->col, ptr);
      strcpy(maze->map[i], temp);
      maze->map[i][maze->col-1] = '\0';
   }
   
   //Print map to stdout
   printf("\n\tBefore Traversal\n");
   for (int i = 0; i < maze->row; ++i)
      printf("\t%s", maze->map[i]);
   printf("\n"); 

   temp = NULL;
   free(temp);
   fclose(ptr);

   return 1;
}



/*
traverse_maze() assigns the starting orientation depending on the location of the maze
entry point. It uses dynamically allocated pointers to integers x and y that are passed
into move_tile() to modify the maze map, along with a dynamically allocated char pointer
attempt that is also passed in to move_tile() to determine the tile to check.
*/
void traverse_maze(struct params *maze){
   char *dir = (char *) malloc(sizeof(char));         //Current orientation
   int *x = (int *) malloc(sizeof(int));              //Current horizontal position
   int *y = (int *) malloc(sizeof(int));              //Current vertical position
   char *attempt = (char*) malloc(sizeof(char));      //Current movement attempt

   //Start at entry point
   x = &maze->x_entry;
   y = &maze->y_entry;

   //Determine orientation: north, south, east, or west
   if(maze->x_entry == 0)
      *dir = 'e';
   else if(maze->x_entry == maze->col-3)
      *dir = 'w';
   else if(maze->y_entry == 0)
      *dir = 's';
   else if(maze->y_entry == maze->row-1)
      *dir = 'n';
   maze->map[*y][*x] = 'W';
   
   //While current position is not the exit point
   while(*x != maze->x_exit || *y != maze->y_exit){   

      //If facing south, attempt to move west
      if(*dir == 's'){
         *attempt = 'w';
      } 
      //If facing north, attempt to move east
      else if(*dir == 'n'){
         *attempt = 'e';
      }
      //If facing east, attempt to move south
      else if(*dir == 'e'){
         *attempt = 's';
      }
      //If facing west, attempt to move north
      else if(*dir == 'w'){
         *attempt = 'n'; 
      }
      *dir = move_tile(maze, x, y, attempt);

      //Update the current tile to a 'W' after moving
      maze->map[*y][*x] = 'W';
   }
   
   //Print fully traversed maze map
   printf("\n\tAfter Traversal\n");
   for (int i = 0; i < maze->row; ++i)
      printf("\t%s", maze->map[i]);
   printf("\n"); 

/*
   dir = NULL;
   x = NULL;
   y = NULL;
   attempt = NULL;
*/

   free(dir);
   free(x);
   free(y);
   free(attempt);

   return;
}



/*
move_tile() is a recursive function that invokes itself until a directional movement
is accomplished. Each time it calls itself, the movement attempt is updated. When
a successful direction of movement is eventually found, the current position in the matrix
is updated and the orientation is passed back to the traverse_maze() call.
*/
char move_tile(struct params *maze, int *x, int *y, char *attempt){
   
   //If attempting to move west and tile is valid, update horizontal position
   if(*attempt == 'w' && maze->map[*y][(*x)-1] != 'X'){
      (*x)--;
   }
   //Otherwise, attempt to move south
   else if(*attempt == 'w'){
      *attempt = 's';
      *attempt = move_tile(maze, x, y, attempt);
   }

   //If attempting to move south and tile is valid, update vertical position
   else if(*attempt == 's' && maze->map[(*y)+1][*x] != 'X'){
      (*y)++;
   }
   //Otherwise, attempt to move east
   else if(*attempt == 's'){
      *attempt = 'e';
      *attempt = move_tile(maze, x, y, attempt);
   }

   //If attempting to move east and tile is valid, update horizontal position
   else if(*attempt == 'e' && maze->map[*y][(*x)+1] != 'X'){
      (*x)++;
   }
   //Otherwise, attempt to move north
   else if(*attempt == 'e'){
      *attempt = 'n';
      *attempt = move_tile(maze, x, y, attempt);
   }

   //If attempting to move north and tile is valid, update vertical position
   else if(*attempt == 'n' && maze->map[(*y)-1][*x] != 'X'){
      (*y)--;
   }
   //Otherwise, attempt to move west
   else if(*attempt == 'n'){
      *attempt = 'w';
      *attempt = move_tile(maze, x, y, attempt);
   }

   return *attempt;
}

void delete_maze(struct params *maze){
   
   for(int i = 0; i < maze->row; ++i){
      free(maze->map[i]);
   }
   free(maze->map);
   free(maze);
   return;
}
