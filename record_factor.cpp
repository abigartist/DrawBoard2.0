#include "record_factor.h"

void RecordFactor::RespondEvent(message_for_shapes msg)
{
	InitLoader();
	RecordFactor::msg = msg;
	if (msg.event_msg == SETPOINTON) {
		while (!msg.pos.empty()) {
			buffer.push_back(msg.pos.front());//将pos中全部进入缓存
			msg.pos.pop();
		}
		if (!vec.empty() && vec[vec.size() - 1]->IsHaveObj()) {
			vec[vec.size() - 1]->HandleMsg(RecordFactor::msg);
		}
		else {
			NewObject();
		}
		while (!buffer.empty()) {
			buffer.pop_back();
		}
	}
	else if(msg.event_msg == SETPOINTSUSPEND)
	{
		for (int index = RecordFactor::index; index < vec.size(); index++) {
			bool determine = vec[index]->HandleMsg(msg);
			if (determine) {
				RiseTheObjToTop(index);
				if (msg.is_pressed||!vec[index]->OverHandle()) RecordFactor::index = index;
				break;
			}
		}
	}
	else if(msg.event_msg == SETPOINTOFF){
		index = 0;
		for (int index = RecordFactor::index; index < vec.size(); index++) {
			vec[index]->HandleMsg(msg);
		}
	}

	InvalidateRect(hWnd, nullptr, TRUE);
}

void RecordFactor::PaintEvent()
{
	for (int index = 0; index < vec.size(); index++) {
		vec[index]->SetDC(hdc);
		vec[index]->Paint();
	}
}

void RecordFactor::RiseTheObjToTop(int index)
{
	ShapeFactor* temp;
	for (int i = index; i < vec.size() - 1; i++) {
		temp = vec[i+1];
		vec[i+1] = vec[i];
		vec[i] = temp;
	}
}




void RecordFactor::InitLoader()
{
	ShapeContainer* ptr = nullptr;
	shape_loader.push_back(nullptr);//分别代表nullevent和moveevent
	shape_loader.push_back(nullptr);
	ptr = new LineContainer;
	shape_loader.push_back(ptr);
	ptr = new RectContainer;
	shape_loader.push_back(ptr);
	ptr = new CirContainer;
	shape_loader.push_back(ptr);
	ptr = new PolContainer;
	shape_loader.push_back(ptr);
}

void RecordFactor::NewObject()
{
	ShapeFactor* ptr = nullptr;
	ptr = shape_loader[msg.option]->NewObj();
	ptr->SetDes(buffer);
	ptr->HandleMsg(msg);
	vec.push_back(ptr);
	//ShapeFactor* ptr = shape_loader.line_factor.NewObj();
	//ptr->SetDes(buffer);
	//ShapeFactor* ptr = new LineFactor(msg.posx1,msg.posy1,msg.posx2,msg.posy2);
	//vec.push_back(ptr);
}


void RecordFactor::GetWnd(HWND hWnd)
{
	RecordFactor::hWnd = hWnd;
}

void RecordFactor::GetWndDC(HDC hdc)
{
	RecordFactor::hdc = hdc;
}
