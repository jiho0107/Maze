#include <cstdio> 
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <tuple>
#include "Node.h"
using namespace std;

class LinkedQueue {
    Node* front;
    Node* rear;
public:
    LinkedQueue():front(NULL),rear(NULL){}
    ~LinkedQueue() { while (!isEmpty()) delete dequeue(); }
    bool isEmpty() { return front == NULL; }
    void enqueue(int r,int c)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->setRow(r);
        node->setCol(c);
        node->setLink(NULL);
        if (isEmpty()) front = rear = node;
        else {
            rear->setLink(node);
            rear = node;
        }
    }
    Node* dequeue() {
        if (isEmpty()) { //큐가 비었을때
            cout << "큐가 비어있습니다." << endl;
            return NULL;
        }
        //큐가 비어있지않을 때
        Node* delNode = front;
        front = front->getLink();
        if (front == NULL) rear == NULL;
        return delNode;
    }

    void display()
    {
        for (Node* p = front; p != NULL; p = p->getLink())
        {
            p->display();
            cout << " -> ";
        }
    }
};
