#pragma once
#include"../../UIBase.h"

class FontUI : public UIBase
{
private:

public:
	FontUI(des::Vec2f _pos, des::Vec2f _size, des::Vec4d _color) :UIBase(_pos, _size, _color) {};
	void animation();
	void update();
};