#include "LinkedQueue.h"
#include <fstream>
#pragma warning(disable:4996)

class Maze
{
private:
    int width; // 미로의 너비(미로 열 수)
    int height; // 미로의 높이(미로 행 수)
    char** map; // 미로 맵
    int exitRow; // 출구 행
    int exitCol; // 출구 열
    LinkedQueue queue; // 큐
    LinkedQueue fQueue; //최종경로 표시 큐
public:
    Maze()
    {
        init(0, 0);
    }

    ~Maze()
    {
        reset();
    }

    // 미로맵 동적 할당 함수
    void init(int w, int h)
    {
        map = new char* [h];
        for (int i = 0; i < h; i++)
            map[i] = new char[w];
    }

    // 미로 맵 동적 해제 함수
    void reset()
    {
        for (int i = 0; i < height; i++)
            delete[]map[i];
        delete[]map;
    }
    void load(const char* file) // 미로파일 읽어오기
    {
        FILE* fp = fopen(file, "r");
        if (fp == NULL) {
            cout << "파일이 존재하지 않습니다." << endl;
            exit(100);
        }

        int nLine = 1; //미로파일 줄 수, 미로 행 수
        int nChar = 0; //미로파일 글자 수

        char ch; //미로파일에서 한글자씩 읽어온 글자

        while ((ch = getc(fp)) != EOF)
        {
            if (ch == '\n')
                nLine++;
            nChar++;
        }
        height = nLine;
        //width = nChar / (nLine*2);
        width = (nChar + 1) / (nLine * 2);
        fclose(fp);
        init(width, height);

        ifstream fin(file, ios::in);
        char temp;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                fin >> temp;

                map[i][j] = temp;
                if (temp == 'e') //입구
                {
                    queue.enqueue(i, j);
                }
                else if (temp == 'x') //출구
                {
                    exitCol = j;
                    exitRow = i;
                }
            }
            cout << endl;
        }
        fin.close();
    }

    // 경로가 막혀있는지 확인하는 함수
    bool isValidLoc(int r, int c)
    {
        if (r < 0 || c < 0 || r > height - 1 || c > width - 1) // 범위를 벗어나는지 판단 여부
            return false;
        else // 범위를 벗어나지 않는 경우
            return( map[r][c] != '7' && (map[r][c] == '0' || map[r][c] == 'x'));
    }

    // 현재 미로를 화면에 출력하는 함수
    void print()
    {
        cout << "전체 미로의 크기 = " << width << " * " << height << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (map[i][j] == '0') //길
                {
                    cout << "  ";
                }
                else if (map[i][j] == '1') //벽
                {
                    cout << "■";
                }
                else if (map[i][j] == '3') // 탈출 성공했을 경우 출구를 별로 표현
                {
                    cout << "★";
                }
                else if (map[i][j] == '7') //지나온 경로
                {
                    cout << "□"; // 지나온 경로 표시
                }
                else if (map[i][j] == '9') //상하좌우로 탐색해서 큐에 들어간 경우
                {
                    cout << "  ";
                }
                else if (map[i][j] == 'e') //입구
                {
                    cout << "○";
                }
                else if (map[i][j] == 'x') //출구
                {
                    cout << "◎";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    // 미로 탐색 함수
    void searchExit()
    {
        while (!queue.isEmpty()) // 큐가 비어있지 않는 동안
        {
            Node* delNode = queue.dequeue();
            int r = delNode->getRow();
            int c = delNode->getCol();
            fQueue.enqueue(r, c);

            if (exitRow == r && exitCol == c)
            {
                map[r][c] = '3';
                break;
            }
            else //상하좌우로 탐색함
            {
                map[r][c] = '7';
                if (isValidLoc(r + 1, c))
                {
                    queue.enqueue(r + 1, c);
                    map[r + 1][c] = '9';
                }
                if (isValidLoc(r - 1, c))
                {
                    queue.enqueue(r - 1, c);
                    map[r - 1][c] = '9';
                }
                if (isValidLoc(r, c - 1))
                {
                    queue.enqueue(r, c - 1);
                    map[r][c - 1] = '9';
                }
                if (isValidLoc(r, c + 1))
                {
                    queue.enqueue(r, c + 1);
                    map[r][c + 1] = '9';
                }
            }
        }
    }
    void finalPath() {
        fQueue.display();
        cout << "finish!!" << endl;
    }
};