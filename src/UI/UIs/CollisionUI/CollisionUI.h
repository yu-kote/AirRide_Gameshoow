#pragma once
#include"../../UIBase.h"

class CollisionUI : public UIBase
{
private:
	
public:
	CollisionUI(des::Vec2f _pos, des::Vec2f _size, des::Vec4d _color) :UIBase(_pos,_size,_color){};
	void animation();
	void update();
};