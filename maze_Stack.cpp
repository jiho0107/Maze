#include <iostream>
#include <stack>
#include <cstdio>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#define MAX_LIST_SIZE 100;
using namespace std;

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int cnt_x = 0;
int cnt_y = 0;
bool visited[50][50];
vector<int> maze_ex;
vector<vector<int> > maze;
string result = "";

class Node {
    Node* link;
    pair<int, int> point;
public:
    Node( int x = 0, int y = 0 ) {
        link = NULL;
        point = make_pair(x, y);
    }
    ~Node(void) { }
    Node* getLink() { return link; }
    void setLink( Node *p ) { link = p; }
    void display() {
        printf("(%d, %d) ",point.first,point.second);
    }
    bool hashData(int x, int y) { return point == make_pair(x, y); }
    
    pair<int, int> getPoint() {
        return point;
    }
    
    void insertNext( Node *n ) {
        if( n != NULL ) {
            n -> link = link;
            link = n;
        }
    }
    
    Node* removeNext() {
        Node* removed = link;
        if( removed != NULL ) {
            link = removed -> link;
        }
        return removed;
    }
};

class LinkedStack {
    Node* top;
public:
    LinkedStack() { top = NULL; }
    ~LinkedStack() {
        while(!isEmpty()) {
            delete pop();
        }
    }
    bool isEmpty() { return top == NULL; }
    
    void push( Node *p ) {
        if ( isEmpty() ) { top = p; }
        else {
            p -> setLink( top );
            top = p;
        }
    }
    Node* pop() {
        if( isEmpty() ) { return NULL; }
        Node *p = top;
        top = top -> getLink();
        return p;
    }
    Node* peek() { return top; }
    
    void display() {
        for ( Node *p = top; p != NULL; p = p ->getLink() ) {
            p -> display();
        }
    }
};

LinkedStack st;

void search(pair<int, int> start, pair<int, int> exit) {
    visited[start.first][start.second] = true;
    maze[start.first][start.second] = 2;
    result += " (" + to_string(start.first) + "," + to_string(start.second) + ")";
    for (int i = 0; i < 4; i++) {
        int point_x = start.first+dx[i];
        int point_y = start.second+dy[i];
        if (0 <= point_x && point_x < cnt_x && 0 <= point_y && point_y < cnt_y) {
            if (visited[point_x][point_y] == false) {
                st.push(new Node(point_x,point_y));
            }
        }
    }
    printf("Stack : ");
    st.display();
    printf("\n");
    cout << "Route :" << result << endl;
    if (start == exit) {
        for (int i = 0; i < cnt_x; i++) {
            for (int j = 0; j < cnt_y; j++) {
                printf("%d ",maze[i][j]);
            }
            printf("\n");
        }
        printf("\narrive!\n");
        cout << "Final Route :" << result << endl;
    } else if (!st.isEmpty()) {
        for (int i = 0; i < cnt_x; i++) {
            for (int j = 0; j < cnt_y; j++) {
                printf("%d ",maze[i][j]);
            }
            printf("\n");
        }

        printf("\n");
        Node *n = st.pop();
        pair<int, int> next = n -> getPoint();
        search(next, exit);
    } else if (st.isEmpty()) {
        printf("Can't find exit\n");
    }
}


int main() {
    ifstream ifile;
    char line[50];
    
    pair<int, int> start;
    pair<int, int> exit;
    
    ifile.open("maze.txt");
    if (ifile.is_open()) {
        while(ifile.getline(line,sizeof(line))) {
            cnt_y = 0;
            for(int i = 0; i < 50; i++) {
                if(line[i] == 'x') {
                    maze_ex.push_back(0);
                } else {
                    maze_ex.push_back(line[i]-'0');
                }
                if('0'==line[i]||line[i]=='1'||line[i]=='e'||line[i]=='x') {
                    if (line[i] == 'e') {
                        start = make_pair(cnt_x, cnt_y);
                    } else if (line[i] == 'x') {
                        exit = make_pair(cnt_x, cnt_y);
                    }
                    cnt_y++;
                }
            }
            cnt_x++;
            maze.push_back(maze_ex);
            maze_ex.clear();
        }
    }
    ifile.close();
    for (int i = 0; i < cnt_x; i++) {
        for (int j = 0; j < cnt_y; j++) {
            if (maze[i][j] == 1) {
                visited[i][j] = true;
            }
        }
    }
    search(start, exit);
}

//class LinkedQueue {
//    Node* front;
//    Node* rear;
//public:
//    LinkedQueue(): front(NULL), rear(NULL) { }
//    ~LinkedQueue() { while(!isEmpty()) delete dequeue(); }
//    bool isEmpty() { return front == NULL; }
//
//    void enqueue ( Node* p ) {
//        if( isEmpty() ) {front = rear = p;}
//        else {
//            rear -> setLink(p);
//            rear = p;
//        }
//    }
//    Node* dequeue() {
//        if ( isEmpty() ) { return NULL; }
//        Node* p = front;
//        front = front -> getLink();
//        if (front == NULL ) { rear == NULL; }
//        return p;
//    }
//    void display() {
//        printf("[큐 내용] : ");
//        for (Node* p = front; p != NULL; p = p->getLink() ) {
//            p->display();
//        }
//        printf( " \n");
//    }
//};
