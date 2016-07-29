#pragma once
#include "myLib/DesLib.h"
#include "picojson.h"
#include "../Share/Easing/Easing.h"
#include "Types/UIState.h"
#include "Types/EasingType.h"
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include <functional>

class UIBase
{
protected:
	des::Vec2f pos;
	des::Vec2f size;

	des::Vec4d color;

	std::vector<std::function<float(float, float, float)>> easing_function;

	std::string texture_path;
	std::string font;

	std::ifstream fs;
	float a;
	bool start;
	bool end;

	
public:
	UIBase(des::Vec2f _pos, des::Vec2f _size, des::Vec4d _color);

	//
	void easingUpdate();

	void EaseInApply(std::string s,float e,std::function<float(float,float,float)> ease, float time);

	void EaseOutApply();

	float* selectUIState(int state);
	


	///////////////////////ゲッター///////////////////////////////
	//コンスト参照にしてないのは動かなかったから
	float getPosX() {
		return static_cast<float>(pos.x);
	}
	float getPosY() {
		return static_cast<float>(pos.y);
	}
	float getSizeX() {
		return static_cast<float>(size.x);
	}
	float getSizeY() {
		return static_cast<float>(size.y);
	}
	float getColorR() {
		return static_cast<float>(color.x);
	}
	float getColorG() {
		return static_cast<float>(color.y);
	}
	float getColorB() {
		return static_cast<float>(color.z);
	}
	float getColorA() {
		return static_cast<float>(color.w);
	}
	//----------------------------------------------------------


	////////////////////セッター///////////////////////////////
	void setPos(const float& pos_x, const float& pos_y) {
		pos.x = pos_x;
		pos.y = pos_y;
	}
	void setSize(const float& size_x, const float& size_y) {
		size.x = size_x;
		size.y = size_y;
	}
	void setFont(const std::string& str) {
		font = str;
	}
	void setColor(const double& color_r, const double& color_g, const double& color_b, const double& color_a) {
		color.x = color_r;
		color.y = color_g;
		color.z = color_b;
		color.w = color_a;
	}
	//---------------------------------------------------------
};


