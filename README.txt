Kevin Dugas
CS 201 - Rivas
Homework 1 - Maze Traversal
April 13, 2020


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

