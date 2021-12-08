#include <stdio.h>
#include <stdlib.h>
#define RIGHT 1
#define LEFT 3
#define UP 2
#define DOWN 0
#define COL 12
#define ROW 12


    /* We have 5 FUNCTION prototypes: */

// FUNCTION 1: Find the start point from the first column of the input (maze[][1]).
void find_Start(char maze[][COL]);

// FUNCTION 2: Gives maze, current x and y coordinate and direction as an input.
void maze_Traversal(char maze[ROW][COL], size_t xDirection, size_t yDirection, int Dir);

// FUNCTION 3: Print the current state of the maze after each movement.
void print_Maze (char maze[][COL]);

// FUNCTION 4: Determine the validity of the next movement (input coordinates).
int valid_Move(char maze[][COL], size_t r, size_t c);

// FUNCTION 5: Check the input coordinates are edge or not.
int coords_edge (size_t x, size_t y);

// Declaration for the coordinate of starting position.
int first_X_cor, first_Y_cor;


// Main function.
int main(){
    // Initialize a maze (2-D array of characters).
    char maze[ROW][COL] = { { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
                            { '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
                            { '0', '0', '1', '0', '1', '0', '1', '1', '1', '1', '0', '1'},
                            { '1', '1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
                            { '1', '0', '0', '0', '0', '1', '1', '1', '0', '1', '0', '0'},
                            { '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
                            { '1', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
                            { '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
                            { '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
                            { '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
                            { '1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
                            { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'} };
    
    find_Start(maze); // Looking for the the zero in first column.
    maze_Traversal(maze, first_X_cor, first_Y_cor, RIGHT);  //Call this function to run the program.
}


/* Objective: Find the start point from the first column of the input maze (maze[][1]).
 Input: Array.
 Output: The fisrt position in the maze. 
 */
void find_Start(char maze[][COL])
{
    int x;
    first_Y_cor = 0;
    for (x = 0; x < ROW; x++)
    {
        if (maze[x][first_Y_cor] == '0')   // Check if the first position is '0'.
        {
            first_X_cor = x;        // If we found the '0', decide it is the first position.
            return;
        }
    }
}


/* Objective: Recursive function gives maze, current x and y coordinates and direction as an input.
 Input: Maze, first coordinate for x and y.
 Output: Decide the next move.
*/
void maze_Traversal(char maze[ROW][COL], size_t xDirection, size_t yDirection, int Dir)
{
    int position = 0;      // Declare and set the start position to zero.   
    
    maze[xDirection][yDirection] = 'x';    // Set the x in the entrance position.

    print_Maze(maze);       // Call the function to display the array.

    // Check if we are in the starting position.
    if (xDirection == first_X_cor && yDirection == first_Y_cor && position == 1)
    {
        printf ("\n***Starting Position***\n");
        return;
    }
    // Check if we are not in the starting position.
    else if ((coords_edge(xDirection,yDirection) && xDirection != first_X_cor) && yDirection != first_Y_cor)
    {
        printf ("\n***Done!***\n");
        return;
    }
    else
    {
        // Declare counter n and next move variables.
        int n, next;
        position = 1;
        
        for (n = 0, next = Dir; n<4; n++, next++, next %= 4)    // Loop through 4 direction.
        {
            switch(next)
            {
                case RIGHT:
                    if (valid_Move(maze, xDirection, yDirection + 1))     // Check if we have '0' in position y+1.
                    {
                        // Recursively call the fuction to go one step in the DOWN direction.
                        maze_Traversal(maze, xDirection, yDirection + 1, DOWN);
                        return;
                    }
                    break;

                case LEFT:
                    if (valid_Move(maze, xDirection, yDirection - 1))      // Check if we have '0' in position y-1.
                    {
                        // Recursively call the fuction to go one step in the UP direction.
                        maze_Traversal(maze, xDirection, yDirection - 1, UP);
                        return;
                    }
                    break;
                
                case UP:
                    if (valid_Move(maze, xDirection - 1, yDirection))      // Check if we have '0' in position x-1.
                    {
                        // Recursively call the fuction to go one step in the RIGHT direction.
                        maze_Traversal(maze, xDirection-1, yDirection, RIGHT);
                        return;
                    }
                    break;

                case DOWN:
                    if (valid_Move(maze, xDirection + 1, yDirection))     // Check if we have '0' in position x+1.
                    {
                        // Recursively call the fuction to go one step in the LEFT direction.
                        maze_Traversal(maze, xDirection + 1, yDirection, LEFT);
                        return;
                    }
                    break;
            }
        }
    }
}


/* Objective: Print the current state of the maze after each movement.
 Input: Array (ROW * COL)
 Output: Display the array on the screen.
*/
void print_Maze (char maze[][COL])
{
    size_t x,y;   // Count row and column.

    for (x = 0; x < ROW; ++x)    // Display the rows.
    {
        for (y=0; y < COL; ++y)   // Display the columns.
        {
            printf ("%c", maze[x][y]);
        }
        puts ("");   // To make sure the array is not displayed in the same line.
    }
    printf ("\n\n");    // To separate each time when the array displayed by 2 break lines.
}


/* Objective: Determine the validity of the next movement (input coordinates).
 Input: Array, x coordinate and y coordinate.
 Output: Return '0' or '1' (valid next movement or not?).
 */
int valid_Move(char maze[][COL], size_t r, size_t c)
{
    // Make sure that we are moving through the zero and not exceeding the 2 dimension array boundary.
    return (r >= 0 && r <= 11 && c >= 0 && c <= 11 && maze[r][c] != '1');
}


/* Objective: Check the input coordinates are edge or not.
 Input: x coordinate and y coordinate.
 Output: Return if there is edge or not.
 */
int coords_edge (size_t x, size_t y)
{
    int edge;
    // Check the outer walls of the maze and return 1.
    if (((x == 0 || x == 11) && (y >= 0 && y <= 11)) || ((x >= 0 && x <= 11) && (y == 0 || y == 11)))
        edge = 1;
    else 
        edge = 0;    // Otherwise, we are inside the maze and return 0.
    return edge;
}