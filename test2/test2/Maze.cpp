#include "Maze.h"

int main(void)
{
    Maze maze;
    maze.load("./maze.txt");

    printf("�̷�\n");
    maze.print();

    printf("�̷� ��� ã��\n");
    maze.searchExit();
    maze.print();
    
    printf("���� ���\n");
    maze.finalPath();
}