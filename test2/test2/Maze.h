#include "LinkedQueue.h"
#include <fstream>
#pragma warning(disable:4996)

class Maze
{
private:
    int width; // �̷��� �ʺ�(�̷� �� ��)
    int height; // �̷��� ����(�̷� �� ��)
    char** map; // �̷� ��
    int exitRow; // �ⱸ ��
    int exitCol; // �ⱸ ��
    LinkedQueue queue; // ť
    LinkedQueue fQueue; //������� ǥ�� ť
public:
    Maze()
    {
        init(0, 0);
    }

    ~Maze()
    {
        reset();
    }

    // �̷θ� ���� �Ҵ� �Լ�
    void init(int w, int h)
    {
        map = new char* [h];
        for (int i = 0; i < h; i++)
            map[i] = new char[w];
    }

    // �̷� �� ���� ���� �Լ�
    void reset()
    {
        for (int i = 0; i < height; i++)
            delete[]map[i];
        delete[]map;
    }
    void load(const char* file) // �̷����� �о����
    {
        FILE* fp = fopen(file, "r");
        if (fp == NULL) {
            cout << "������ �������� �ʽ��ϴ�." << endl;
            exit(100);
        }

        int nLine = 1; //�̷����� �� ��, �̷� �� ��
        int nChar = 0; //�̷����� ���� ��

        char ch; //�̷����Ͽ��� �ѱ��ھ� �о�� ����

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
                if (temp == 'e') //�Ա�
                {
                    queue.enqueue(i, j);
                }
                else if (temp == 'x') //�ⱸ
                {
                    exitCol = j;
                    exitRow = i;
                }
            }
            cout << endl;
        }
        fin.close();
    }

    // ��ΰ� �����ִ��� Ȯ���ϴ� �Լ�
    bool isValidLoc(int r, int c)
    {
        if (r < 0 || c < 0 || r > height - 1 || c > width - 1) // ������ ������� �Ǵ� ����
            return false;
        else // ������ ����� �ʴ� ���
            return( map[r][c] != '7' && (map[r][c] == '0' || map[r][c] == 'x'));
    }

    // ���� �̷θ� ȭ�鿡 ����ϴ� �Լ�
    void print()
    {
        cout << "��ü �̷��� ũ�� = " << width << " * " << height << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (map[i][j] == '0') //��
                {
                    cout << "  ";
                }
                else if (map[i][j] == '1') //��
                {
                    cout << "��";
                }
                else if (map[i][j] == '3') // Ż�� �������� ��� �ⱸ�� ���� ǥ��
                {
                    cout << "��";
                }
                else if (map[i][j] == '7') //������ ���
                {
                    cout << "��"; // ������ ��� ǥ��
                }
                else if (map[i][j] == '9') //�����¿�� Ž���ؼ� ť�� �� ���
                {
                    cout << "  ";
                }
                else if (map[i][j] == 'e') //�Ա�
                {
                    cout << "��";
                }
                else if (map[i][j] == 'x') //�ⱸ
                {
                    cout << "��";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    // �̷� Ž�� �Լ�
    void searchExit()
    {
        while (!queue.isEmpty()) // ť�� ������� �ʴ� ����
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
            else //�����¿�� Ž����
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