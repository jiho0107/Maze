#include <cstdio>
class Node {
	Node* link; //링크
	int row; //행
	int col; //열
public:
	Node(int r,int c) : row(r),col(c){}
	Node* getLink() { return link; }
	void setLink(Node* next) { link = next; }
	void display() {
		printf(" (%d,%d) ", row, col); //행,열을 보여줌
	}
	int getRow() { return row; }
	void setRow(int r) { row = r; }
	int getCol() { return col; }
	void setCol(int c) { col = c; }
};
