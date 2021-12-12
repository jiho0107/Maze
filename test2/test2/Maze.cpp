#include "Maze.h"

int main(void)
{
    Maze maze;
    maze.load("./maze.txt");

    printf("미로\n");
    maze.print();

    printf("미로 경로 찾기\n");
    maze.searchExit();
    maze.print();
    
    printf("최종 경로\n");
    maze.finalPath();
}