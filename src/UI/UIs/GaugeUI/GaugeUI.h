#pragma once
#include"../../UIBase.h"

class GaugeUI : public UIBase
{
private:

public:
	GaugeUI(des::Vec2f _pos, des::Vec2f _size, des::Vec4d _color) :UIBase(_pos, _size, _color) {};
	void animation();
	void update();
};