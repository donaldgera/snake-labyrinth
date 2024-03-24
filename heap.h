/**
 * @file heap.h
 * @author Donald Gera
 */

#include "my_functions.h"

/** @struct heap_t
 *  @brief Structure representing a max heap.
 */
typedef struct {
    int capacity; /**< Maximum capacity of the heap. */
    int size; /**< Current size of the heap. */
    maze_t *arr_maze; /**< Array of mazes stored in the heap. */
} heap_t;

/**
 * @brief Creates a new max heap with the specified capacity.
 * @param capacity The initial capacity of the heap.
 * @return A pointer to the newly created heap.
 */
heap_t* create_heap(int capacity);

/**
 * @brief Resizes the heap to the specified capacity.
 * @param h Pointer to the heap.
 * @param capacity The new capacity for the heap.
 */
void resize_heap(heap_t *h, int capacity);

/**
 * @brief Inserts a maze into the heap.
 * @param h Pointer to the heap.
 * @param maze Pointer to the maze_t object to be inserted.
 */
void insert(heap_t* h, maze_t *maze);

/**
 * @brief Helper function that is used to re-organize the heap after insertion. This function is called after every insertion of an element in a heap to maintain the property of the max heap.
 * @param h Pointer to the heap.
 * @param index The index at which to perform insertion.
 */
void insert_aux(heap_t* h, int index);

/**
 * @brief Restores the max-heap property starting from the given index.
 * @param h Pointer to the heap.
 * @param index The index from which to start the max-heapify process.
 */
void max_heapify(heap_t* h, int index);

/**
 * @brief Extracts the maze with the highest score (maze->score + maze->coins * 10) from the heap.
 * @param h Pointer to the heap.
 * @return Pointer to the maze_t object with the highest score.
 */
maze_t *extract_max(heap_t* h);

/**
 * @brief Checks if the heap is empty.
 * @param h Pointer to the heap.
 * @return true if the heap is empty, false otherwise.
 */
bool empty_heap(heap_t *h);

/**
 * @brief Destroys the heap and frees the associated memory.
 * @param h Pointer to the heap to be destroyed.
 */
void destroy_heap(heap_t *h);