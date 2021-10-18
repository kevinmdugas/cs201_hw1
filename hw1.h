//Kevin Dugas
//CS 201 - Rivas
// Homework 1 - Maze Traversal
// April 13, 2020

/*
This program builds a maze using specifications read in from a file and traverses the maze using the following algorithm:
   1) If the tile to the right is not a wall, move to that tile
   2) Else if the tile straight ahead is not a wall, move to that tile
   3) Else if the tile to the left is not a wall, move to that tile
   4) Otherwise move to the tile behind the current tile
The file is passed in as a command line argument by stdin and adheres to the following format:
   Line 1 has two integers separated by a comma that indicate the dimensions of the maze
   Line 2 has two integers separated by a comma that indicate the entry point coordinates of the maze
   Line 3 has two integers separated by a comma that indicate the exit point coordinates of the maze
   Every subsequent line in the file is one line of the maze
After the maze parameters are read in, a 2D array is constructed to hold the maze map and the above algorithm is employed
to traverse the maze. Once the maze is successfully traversed, its map with the traversed path is printed to stdout.
*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 20

//The params struct groups the parameters of the maze together for more
// contained function arguments.
struct params{
   int row, col;              //Dimensions of the maze
   int x_entry, y_entry;      //Entry coordinates
   int x_exit, y_exit;        //Exit coordinates
   char ** map;               //2D array containing maze
};

//Prototypes of functions whose implentation is in the file "hw1_func.c"
int get_params(char file[], struct params *maze);
int build_maze(char file[], struct params *maze);
void traverse_maze(struct params *maze);
char move_tile(struct params *maze, int *x, int *y, char *attempt);
void delete_maze(struct params *maze);

