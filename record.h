#define LINE 1
#define RECT 2
#define CIR 3
#define MOVE 0
#define MAX_SHAPE 500
#define rep(count) \
    for (int index = 0; index < count; index++)
#define rep_2(i,j) \
    for (int index = i; index < j; index++)
#define repop(count) \
    for (int index = count-1; index >= 0; index--)
/*
   rep()有一个参数的for循环
   rep_2()有两个参数的for循环
*/
#include <iostream>

using std::cin;
using std::cout;

struct DesAndShape {
	int shape;
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
};

class RecordStack
{
public:
	RecordStack();
	int push(int shape, int x1, int y1, int x2, int y2, int x3, int y3);
	bool clicked(int x, int y);
	void swap(int index1, int index2);
	int GetStackTop();
	DesAndShape OutPoint(int index);
	void AddDx(int dx, int dy);
	//void change(int index,int shape, int x1, int y1, int x2, int y2);
	~RecordStack() {};
private:
	DesAndShape array[MAX_SHAPE];
	int StackTop;
	int OutCount;
};

