#pragma once
#include"../../UIBase.h"

class BarCollisionUI : public UIBase
{
private:

public:
	BarCollisionUI(des::Vec2f _pos, des::Vec2f _size) :UIBase(_pos, _size) {};
	void animation();
	void update();
};