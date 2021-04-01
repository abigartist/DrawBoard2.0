#include <vector>
#include "shape_factor.h"
#include "line_factor.h"
#include "rect_factor.h"
#include "cir_factor.h"
#include "pol_factor.h"

#define MAXSHAPE 10
#define MAXPOINT 100
#define END -1
//record类作为中轴线串连各个类
using std::vector;

class RecordFactor
{
public:
	RecordFactor() = default;
	~RecordFactor()=default;
	void RespondEvent(message_for_shapes msg);
	void GetWnd(HWND hWnd);
	void GetWndDC(HDC hdc);
	void PaintEvent();
	void RiseTheObjToTop(int index);
	vector<ShapeFactor*> vec;
private:
	HDC hdc;
	message_for_shapes msg;
	HWND hWnd;
	vector<int> buffer;
	vector<ShapeContainer*> shape_loader;
	void InitLoader();
	//ShapeContainer<ShapeFactor> shape_container[MAXPOINT];
	int slFlag = 0;
	int index = 0;
	void NewObject();
};

