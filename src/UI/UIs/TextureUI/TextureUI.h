#pragma once
#include "../../UIBase.h"

class TextureUI : public UIBase
{
private:

public:
	TextureUI(des::Vec2f _pos, des::Vec2f _size) :UIBase(_pos, _size) {};
	void animation();
	void update();
};