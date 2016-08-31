#pragma once
#include"../../UIBase.h"

class FontUI : public UIBase
{
private:
	std::string font_path;
	std::string text;
public:
	FontUI(des::Vec2f _pos, des::Vec2f _size, des::Vec4d _color) :UIBase(_pos, _size, _color) 
	{
		own_ui = UITYPE::FontUI;
		color = des::Vec4f(0.0f,0.0f,0.0f,1.0f);
	};
	std::string fontGetText() {
		return text;
	}
	std::string fontGetPath() {
		return font_path;
	}
	float fontGetSize() {
		return size.x;
	}
	void fontSetText(const std::string& text) {
		this->text = text;
	}
	void fontSetPath(const std::string& font_path) {
		this->font_path = font_path;
	}
	void fontSetSize(const float& size) {
		this->size.x = size;
	}
};