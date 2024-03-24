/**
 * @file my_functions.h
 * @author Donald Gera
 * @brief Collection of functions and AI used to find a path to the exit of the labyrinth
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>

/** @struct position_t
 *  @brief Structure representing a pair for the positions in the maze.
 */
typedef struct {
    int x; /**< The X coordinate of the position. */
    int y; /**< The Y coordinate of the position. */
} position_t;

/** @brief Creates a position_t with the given coordinates.
 *  @param x The x-coordinate of the position.
 *  @param y The y-coordinate of the position.
 *  @return The created position_t.
 */
position_t create_pos(int x, int y);

/**
 * @brief Moves a position by a given direction.
 * This function takes a starting position and a movement direction
 * character and returns the new position after the movement.
 * @param pos The starting position.
 * @param move The movement direction character ('N', 'S', 'O', 'E').
 * @return The new position after the movement.
 */
position_t move_pos(position_t pos, char move);


/** @struct maze_t
 *  @brief Structure representing a maze.
 */
typedef struct {
    char* matrix;       /**< Pointer to the maze matrix. */
    position_t start;   /**< The starting position in the maze. */
    position_t end;     /**< The ending position in the maze. */
    position_t current; /**< The current position in the maze. */
    int rows;           /**< The number of rows in the maze. */
    int cols;           /**< The number of columns in the maze. */
    int coins;          /**< The number of coins collected. */
    int drills;         /**< The number of drills available. */
    int score;
    char* path;         /**< The path taken in the maze (directions). */
} maze_t;

/** @brief Takes input (length, height of the maze and the structure of the maze) and sets up the maze.
 *  @param maze Pointer to the maze_t structure to set up.
 */
void take_input_and_set_maze(maze_t *maze);

/** @brief Initializes and sets up the maze.
 *  @return A pointer to the initialized maze_t structure.
 */
maze_t *iniz_maze();

/**
 * @brief Creates a deep copy of a maze.
 * @param maze Pointer to the original maze to be copied.
 * @return Pointer to the new maze_t object, which is a copy of the original maze.
 */
maze_t *copy_maze(maze_t *maze);

/**
 * @brief Destroys a maze and frees associated memory.
 * @param maze Pointer to the maze_t object to be destroyed.
 */
void destroy_maze(maze_t *maze);

/** @brief Sets the value at a specific position in the maze matrix.
 *  @param maze Pointer to the maze_t structure.
 *  @param pos The position to set the value at.
 *  @param val The value to set at the specified position.
 */
void set_pos_maze(maze_t *maze, position_t pos, char val);

/** @brief Gets the value at a specific position in the maze matrix.
 *  @param maze Pointer to the maze_t structure.
 *  @param pos The position to get the value from.
 *  @return The value at the specified position.
 */
char get_pos_maze(maze_t *maze, position_t pos);

/** @brief Prints in output the maze with the covered path and the snake with its body.
 */
void print_maze(maze_t *maze);

/** @brief Prints the path covered in the maze.
 *  @param maze Pointer to the maze_t structure.
 */
void print_path_maze(maze_t *maze);

/** @brief Computes the score reached in the maze.
 *  @param maze Pointer to the maze_t structure.
 */
int get_score_maze(maze_t *maze);

/** @brief Checks if the current position in the maze is the end of the maze.
 *  @param maze Pointer to the maze.
 *  @return true if the current position is the end position, false otherwise.
 */
bool is_end_of_maze(maze_t *maze);

/**
 * @brief Checks if the player can move to the given position in the maze.
 * @param maze Pointer to the maze_t object.
 * @param pos The position to check.
 * @return true if the player can move to the given position, false otherwise.
 */
bool check_move(maze_t *maze, position_t pos);

/**
 * @brief Checks if the snake is eating his tail, if so computes the number of coins left in the maze.
 * @param maze Pointer to the maze_t object.
 * @return The number of coins left in the maze given.
 */
int check_is_tail(maze_t *maze);

/**
 * @brief Moves the player's current position in the maze based on the given movement direction character.
 * @param maze Pointer to the maze_t object.
 * @param move The movement direction character ('N', 'S', 'O', 'E').
 */
void move(maze_t *maze, char move);

/**
 * @brief Similar to void move(maze_t *maze, char move) it just lets the player pass on a position as many times as he wants
 * @param maze Pointer to the maze_t object.
 * @param move The movement direction character ('N', 'S', 'O', 'E').
 */
void move_interactive(maze_t *maze, char move);


/** @brief Calls the move function in order to move snake's current position and gives feedback to the player if the direction character is not admissible.
 *  @param maze Pointer to the maze_t structure.
 *  @param c The direction character ('N', 'S', 'O', 'E').
 */
void player_move(maze_t* maze, char c);

/**
 * @brief Replays a sequence of movement direction characters from
 * the provided path. It simulates the player's movements according to the recorded path and updates the maze state
 * accordingly.
 * @param maze Pointer to the maze where to perform the path.
 * @param path Pointer to a path of movement direction characters ('N', 'S', 'O', 'E').
 */
void replay(maze_t *maze, char* path);

/**
 * @brief Function for the AI's algorithm based on Dijkstra's algorithm.
 * @param maze Pointer to the maze.
 * @param result Pointer to the char array to store the resulting path.
 * @param matrix Pointer to a matrix that stores the maximum score for each cell in the maze.
 * @param score The score associated with the calculated path.
 */
void AI_Dijkstra_Aux(maze_t *maze, char* result, int *matrix, int score);

/**
 * @brief Function that initializes the structures used in void AI_Dijkstra_Aux()
 * @param maze Pointer to the maze.
 */
void AI_Dijkstra(maze_t *maze);

/** @brief Enters the interactive mode for the maze.
 *  @param maze Pointer to the maze.
 */
void interactive_mode(maze_t* maze);

