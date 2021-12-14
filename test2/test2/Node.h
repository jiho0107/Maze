#include <cstdio>
class Node {
	Node* link; //��ũ
	int row; //��
	int col; //��
public:
	Node(int r,int c) : row(r),col(c){}
	Node* getLink() { return link; }
	void setLink(Node* next) { link = next; }
	void display() {
		printf(" (%d,%d) ", row, col); //��,���� ������
	}
	int getRow() { return row; }
	void setRow(int r) { row = r; }
	int getCol() { return col; }
	void setCol(int c) { col = c; }
};
