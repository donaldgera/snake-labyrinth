/**
 * @file heap.c
 * @author Donald Gera
 * @brief Implementation of maxheap
 */

#include "heap.h"

heap_t* create_heap(int capacity){
    heap_t* h = (heap_t*)malloc(sizeof(heap_t));
    if (h == NULL) exit(EXIT_FAILURE);

    h->size = 0;
    h->capacity = capacity;

    h->arr_maze = (maze_t*)malloc(capacity * sizeof(maze_t));
    if (h->arr_maze == NULL) exit(EXIT_FAILURE);

    return h;
}

void resize_heap(heap_t *h, int capacity){
    h->capacity = capacity;
    h->arr_maze = realloc(h->arr_maze, capacity * sizeof(maze_t));
}

void insert(heap_t* h, maze_t *maze){
    if (h->size == h->capacity) resize_heap(h, h->capacity * 2);
    
    if (h->size < h->capacity) {
        maze_t* temp = copy_maze(maze);
        h->arr_maze[h->size] = *temp;

        insert_aux(h, h->size);
        h->size++;
    }
}

void insert_aux(heap_t* h, int index){
    if(index == 0)
        return;
    int parent = (index - 1) / 2;
    if (get_score_maze(&h->arr_maze[parent]) < get_score_maze(&h->arr_maze[index])){
        maze_t temp = h->arr_maze[parent];
        h->arr_maze[parent] = h->arr_maze[index];
        h->arr_maze[index] = temp;

        insert_aux(h, parent);
    }
}

maze_t *extract_max(heap_t* h){
    if (empty_heap(h)) printf("\nHeap is empty\n");
    maze_t* extracted;
    extracted = copy_maze(&h->arr_maze[0]);
    h->arr_maze[0] = h->arr_maze[h->size - 1];
    h->size--;

    max_heapify(h, 0);
    return extracted;
}

void max_heapify(heap_t* h, int index){
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int max;
 
    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;
 
    if (left != -1 && get_score_maze(&h->arr_maze[left]) > get_score_maze(&h->arr_maze[index]))
        max = left;
    else max = index;
    if (right != -1 && get_score_maze(&h->arr_maze[right]) > get_score_maze(&h->arr_maze[max]))
        max = right;
 
    if (max != index) {
        maze_t temp = h->arr_maze[index];
        h->arr_maze[index] = h->arr_maze[max];
        h->arr_maze[max] = temp;

        max_heapify(h, max);
    }
}

bool empty_heap(heap_t *h){
    return h->size == 0;
}

void destroy_heap(heap_t *h){
    free(h->arr_maze);
    free(h);
}