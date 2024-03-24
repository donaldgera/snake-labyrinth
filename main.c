/**
 * @file main.c
 * @author Donald Gera
 */

#include "my_functions.c"

int main(int argc, char **argv){
    maze_t *maze = iniz_maze();
    int mode = 0;
    while(mode != 1 && mode != 2 && mode != 3){
        printf("1 Interactive Mode   2 AI_Rec   3 AI_Best\n");
        scanf("%d", &mode);
        if(mode == 1) interactive_mode(maze);
        if(mode == 2) AI_recursive(maze);
        if(mode == 3) AI_Dijkstra(maze);
    }
    return 0;
}
