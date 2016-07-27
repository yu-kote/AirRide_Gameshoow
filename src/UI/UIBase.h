#pragma once
#include "myLib/DesLib.h"
#include "picojson.h"
#include "Easing/Easing.h"
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>


class UIBase
{
protected:
	des::Vec2d pos;
	des::Vec2d size;

	//des::Vec4d color;

	std::string texture_path;
	std::string font;

	std::ifstream fs;

	bool start;
	bool end;

	
public:
	UIBase(des::Vec2f _pos, des::Vec2f _size) : pos(_pos), size(_size) {
		start = false;
		end = false;
	}

	//
	void easingUpdate();

	//void EaseInApply(std::string s,float e,);

	void EaseOutApply();





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
	//----------------------------------------------------------


	////////////////////セッター///////////////////////////////
	void setPos(const float& pos_x, const float& pos_y) {
		pos.x = pos_x;
		pos.y = pos_y;
	}
	void setPos(const double& pos_x, const double& pos_y) {
		pos.x = pos_x;
		pos.y = pos_y;
	}
	void setSize(const float& size_x, const float& size_y) {
		size.x = size_x;
		size.y = size_y;
	}
	void setSize(const double& size_x, const double& size_y) {
		size.x = size_x;
		size.y = size_y;
	}
	void setFont(const std::string& str) {
		font = str;
	}
	//---------------------------------------------------------
};


