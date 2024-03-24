/**
 * @file my_functions.h
 * @author Donald Gera
 */

#include "heap.c"
#include <ctype.h>

int pathlength = 0;
char moves[] = {'N', 'E', 'S', 'O'};
const int default_score = 1000;
const int default_drills = 0;
const int default_coins = 0;

position_t create_pos(int x, int y){
    return (position_t) {x, y};
}

position_t move_pos(position_t pos, char move){
    if(move == 'N') return (position_t) {pos.x + 0, pos.y - 1};
    if(move == 'S') return (position_t) {pos.x + 0, pos.y + 1};
    if(move == 'O') return (position_t) {pos.x - 1, pos.y + 0};
    if(move == 'E') return (position_t) {pos.x + 1, pos.y + 0};
}

void take_input_and_set_maze(maze_t *maze){
    int c, r;
    scanf("%d",&c);
    scanf("%d",&r); 

    pathlength = c * r;
    maze->cols = c;
    maze->rows = r;
    maze->matrix = (char*)malloc(maze->cols * maze->rows * sizeof(char));
    if(maze->matrix == NULL) exit(EXIT_FAILURE);
    getchar();
    for(int i = 0; i < maze->rows; i++){
        for(int j = 0; j < maze->cols; j++){
            maze->matrix[i*maze->cols + j] = getchar();
            if(maze->matrix[i*maze->cols + j] == '_'){
                maze->end = create_pos(j, i);
            }
            else if(maze->matrix[i*maze->cols + j] == 'o'){
                maze->start = create_pos(j, i);
                maze->current = create_pos(j, i);
            }
        }
        getchar();
    }

    maze->path = (char*)malloc(pathlength * sizeof(char));
    if(maze->path == NULL) exit(EXIT_FAILURE);
    strcpy(maze->path, "\0");
    
    maze->coins = default_coins;
    maze->drills = default_drills;
    maze->score = default_score;
}

maze_t *iniz_maze(){
    maze_t *maze = (maze_t*)malloc(sizeof(maze_t));
    if(maze == NULL) exit(EXIT_FAILURE);
    take_input_and_set_maze(maze);
    return maze;
}

maze_t *copy_maze(maze_t *maze){
    maze_t *maze_copy = malloc(sizeof(maze_t));
    if(maze_copy == NULL) exit(EXIT_FAILURE);
    maze_copy->cols = maze->cols;
    maze_copy->rows = maze->rows;
    maze_copy->coins = maze->coins;
    maze_copy->drills = maze->drills;
    maze_copy->score = maze->score;
    maze_copy->matrix = (char*)malloc(maze->cols * maze->rows * sizeof(char));
    if(maze_copy->matrix == NULL) exit(EXIT_FAILURE);
    for(int i = 0; i < maze->rows; i++){
        for(int j = 0; j < maze->cols; j++){
            maze_copy->matrix[i * maze->cols + j] = maze->matrix[i * maze->cols + j];
        }
    }

    maze_copy->path = (char*)malloc(sizeof(char) * pathlength);
    if(maze_copy->path == NULL) exit(EXIT_FAILURE);
    strcpy(maze_copy->path, maze->path);

    maze_copy->start = maze->start;
    maze_copy->current = maze->current;
    maze_copy->end = maze->end;

    return maze_copy;
}

void destroy_maze(maze_t *maze){
    free(maze->matrix);
    free(maze->path);
    free(maze);
}

void set_pos_maze(maze_t *maze, position_t pos, char val) {
    maze->matrix[pos.y * maze->cols + pos.x] = val;
}

char get_pos_maze(maze_t *maze, position_t pos) {
    return maze->matrix[pos.y * maze->cols + pos.x];
}

void print_maze(maze_t *maze_c){
    maze_t *maze = copy_maze(maze_c);
    position_t pos = create_pos(maze->current.x, maze->current.y);

    int length_path = strlen(maze->path) - 1;
    for(int i = 0; i < maze->coins; i++){
        if(maze->path[length_path] == 'N'){
            pos = move_pos(pos, 'S');
            set_pos_maze(maze, pos, 248);
        }
        else if(maze->path[length_path] == 'E'){
            pos = move_pos(pos, 'O');
            set_pos_maze(maze, pos, 248);
        }
        else if(maze->path[length_path] == 'S'){
            pos = move_pos(pos, 'N');
            set_pos_maze(maze, pos, 248);
        }
        else if(maze->path[length_path] == 'O'){
            pos = move_pos(pos, 'E');
            set_pos_maze(maze, pos, 248);
        }
        length_path--;
    }
    for(int i = 0; i < maze->rows; i++){
        for(int j = 0; j < maze->cols; j++){
            if(i == maze->current.y && j == maze->current.x)
                printf("o");
            else if((maze->matrix[i * maze->cols + j] == '-' || maze->matrix[i * maze->cols + j] == '/' || maze->matrix[i * maze->cols + j] == '+')) printf(".");
            else printf("%c", maze->matrix[i * maze->cols + j]);
        }
        printf("\n");
    }
    printf("\n");
    destroy_maze(maze);
}

void print_path_maze(maze_t *maze){
    printf("PATH: %s\n", maze->path);
}

int get_score_maze(maze_t *maze){
    return maze->score + maze->coins * 10 + 2 * maze->drills;
}

bool is_end_of_maze(maze_t *maze){
    return maze->current.y ==  maze->end.y && maze->current.x ==  maze->end.x;
}

bool check_move(maze_t *maze, position_t pos){
    return get_pos_maze(maze, pos) != '+' && (maze->drills > 0 || get_pos_maze(maze, pos) != '#') && pos.y >= 0 && pos.y < maze->rows && pos.x >= 0 && pos.x < maze->cols;
}

int check_is_tail(maze_t *maze){
    int left_coins = 0;
    position_t pos = create_pos(maze->current.x, maze->current.y);
    int length_path = strlen(maze->path) - 1;
    if(maze->path[length_path] == 'N')
        pos = move_pos(pos, 'S');
    else if(maze->path[length_path] == 'E')
        pos = move_pos(pos, 'O');
    else if(maze->path[length_path] == 'S')
        pos = move_pos(pos, 'N');
    else if(maze->path[length_path] == 'O')
        pos = move_pos(pos, 'E');
    while(!(maze->current.y ==  pos.y && maze->current.x ==  pos.x) && length_path-- >= 0){
        if(maze->path[length_path] == 'N')
            pos = move_pos(pos, 'S');
        else if(maze->path[length_path] == 'E')
            pos = move_pos(pos, 'O');
        else if(maze->path[length_path] == 'S')
            pos = move_pos(pos, 'N');
        else if(maze->path[length_path] == 'O')
            pos = move_pos(pos, 'E');
        left_coins++;
    }
    return left_coins;
}

void move(maze_t *maze, char move){
    position_t new_pos = move_pos(maze->current, move);
    if(!check_move(maze, new_pos)) return;
    if(maze->matrix[maze->current.y * maze->cols + maze->current.x] == '/')
        set_pos_maze(maze, maze->current, '+');
    else set_pos_maze(maze, maze->current, '/');
    maze->current = new_pos;
    maze->score--;
    strncat(maze->path, &move, 1);
    char c = get_pos_maze(maze, new_pos);
    if(c == '$') maze->coins++;
    if (c == 'T') maze->drills = maze->drills + 3;
    if (c == '!') maze->coins = maze->coins / 2;
    if (c == '#') maze->drills--;

    if(maze->coins > 0){
        int left_coins = check_is_tail(maze);
        if(left_coins < maze->coins) maze->coins = left_coins;
    }
}

void move_interactive(maze_t *maze, char move){
    position_t new_pos = move_pos(maze->current, move);
    if(!check_move(maze, new_pos)) return;
    set_pos_maze(maze, maze->current, '.');
    maze->current = new_pos;
    maze->score--;
    strncat(maze->path, &move, 1);
    char c = get_pos_maze(maze, new_pos);
    if(c == '$') maze->coins++;
    if (c == 'T') maze->drills = maze->drills + 3;
    if (c == '!') maze->coins = maze->coins / 2;
    if (c == '#') maze->drills--;
    if(maze->coins > 0){
        int left_coins = check_is_tail(maze);
        if(left_coins < maze->coins) maze->coins = left_coins;
    }
}

void player_move(maze_t* maze, char c){
    if(c == 'N') move_interactive(maze, 'N');
    else if(c == 'S') move_interactive(maze, 'S');
    else if(c == 'O') move_interactive(maze, 'O');
    else if(c == 'E') move_interactive(maze, 'E');
    else if(c == '\n');
    else printf("Illegal move! Do another move.\n");
}

void replay(maze_t *maze, char* path){
    printf("\n");
    for(int i = 0; i < strlen(path); i++){
        move(maze, path[i]);
    }
    print_maze(maze);
    print_path_maze(maze);
    printf("SCORE: %d", get_score_maze(maze) - 2 * maze->drills);
}

void AI_Dijkstra_Aux(maze_t *maze, char* path, int *matrix, int score){
    heap_t *heap = create_heap(100);
    insert(heap, copy_maze(maze));
    while(!empty_heap(heap)){
        maze_t *extracted = extract_max(heap);
        maze_t *try = copy_maze(extracted);
        destroy_maze(extracted);

        if(is_end_of_maze(try)){
            int temp_score = get_score_maze(try);
            if(temp_score > score){
                score = temp_score;
                strcpy(path, try->path);
            }
            destroy_maze(try);
        }
        else{
            for(int i = 0; i < 4; i++){
                position_t new_pos = move_pos(try->current, moves[i]);
                if(check_move(try, new_pos)){
                    maze_t *entry = copy_maze(try);
                    move(entry, moves[i]);
                    int new_score = get_score_maze(entry);
                    if(matrix[new_pos.y * try->cols + new_pos.x] < new_score){
                        matrix[new_pos.y * try->cols + new_pos.x] = new_score;
                        insert(heap, entry);
                    }
                    destroy_maze(entry);
                }
            }
            destroy_maze(try);
        }
    }
    destroy_heap(heap);
}

void AI_Dijkstra(maze_t *maze){
    char* result;
    result = (char*)malloc(sizeof(char) * pathlength);
    strcpy(result, "\0");
    int score = INT_MIN;
    int *matrix_opt = (int*)malloc(maze->cols * maze->rows * sizeof(int));
    for(int i = 0; i < maze->rows; i++){
        for(int j = 0; j < maze->cols; j++){
            matrix_opt[i*maze->cols + j] = 0;
        }
    }
    AI_Dijkstra_Aux(maze, result, matrix_opt, score);
    replay(maze, result);
    free(result);
    free(matrix_opt); 
    destroy_maze(maze);
}

void interactive_mode(maze_t* maze){
    printf("If you want to exit press 'e'.\n");
    char c;
    while(!is_end_of_maze(maze)){
        c = getchar();
        if(c == 'e') break;
        player_move(maze, toupper(c));
        if(c != '\n')
            print_maze(maze);
    }
    print_path_maze(maze);
    printf("SCORE: %d\n", get_score_maze(maze));
    destroy_maze(maze);
}

int score_recursive = INT_MIN;
void AI_recursive_aux(maze_t *maze, int *matrix, char *path){
    if (is_end_of_maze(maze) && get_score_maze(maze) > score_recursive){ 
        strcpy(path, maze->path);
        score_recursive = get_score_maze(maze);
        return;
    }
    for (int i = 0; i < 4; i++) {
        maze_t *maze_copy = copy_maze(maze);
        position_t new_pos = move_pos(maze->current, moves[i]);
        if (check_move(maze_copy, new_pos)){
            move(maze_copy, moves[i]);
            int prev_score = matrix[new_pos.y * maze->cols + new_pos.x];
            if (prev_score < get_score_maze(maze_copy)){
                matrix[new_pos.y * maze->cols + new_pos.x] = get_score_maze(maze_copy);
                AI_recursive_aux(maze_copy, matrix, path);
                matrix[new_pos.y * maze->cols + new_pos.x] = prev_score;
            }
        }
        destroy_maze(maze_copy);
    }
}

void AI_recursive(maze_t *maze){
    int *matrix_opt = (int*)malloc(maze->cols * maze->rows * sizeof(int));
    for(int i = 0; i < maze->rows; i++){
        for(int j = 0; j < maze->cols; j++){
            matrix_opt[i*maze->cols + j] = 0;
        }
    }
    char *path = (char*)malloc(sizeof(char) * pathlength);
    strcpy(path, "\0");
    AI_recursive_aux(maze, matrix_opt, path);
    replay(maze, path);
    free(path);
    free(matrix_opt);
    destroy_maze(maze);
}