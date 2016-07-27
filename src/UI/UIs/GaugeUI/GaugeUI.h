#pragma once
#include"../../UIBase.h"

class GaugeUI : public UIBase
{
private:

public:
	GaugeUI(des::Vec2f _pos, des::Vec2f _size) :UIBase(_pos, _size) {};
	void animation();
	void update();
};