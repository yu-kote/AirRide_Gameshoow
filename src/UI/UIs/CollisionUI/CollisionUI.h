#pragma once
#include"../../UIBase.h"

class CollisionUI : public UIBase
{
private:
	
public:
	CollisionUI(des::Vec2f _pos, des::Vec2f _size) :UIBase(_pos,_size){};
	void animation();
	void update();
};