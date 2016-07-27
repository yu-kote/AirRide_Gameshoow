#pragma once
#include"../../UIBase.h"

class FontUI : public UIBase
{
private:

public:
	FontUI(des::Vec2f _pos, des::Vec2f _size) :UIBase(_pos, _size) {};
	void animation();
	void update();
};