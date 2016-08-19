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

struct EasingBuf
{
	EasingBuf(std::string _start, float _end, std::function<float(float, float, float)> _ease, float _time) {
		start = _start;
		end = _end;
		ease = _ease;
		time = _time;
	}
	std::string start;
	float end;
	std::function<float(float, float, float)> ease;
	float time;
};

class UIBase
{
protected:
	des::Vec2f pos;
	des::Vec2f size;

	des::Vec4f color;

	std::vector<std::function<float(float, float, float)>> easing_function;
	std::vector<std::function<void()>> ease_out_function;
	std::string texture_path;
	std::string font;
	
	std::vector<EasingBuf> ease_in_buf;
	std::vector<EasingBuf> ease_end_buf;
	std::vector<EasingBuf> ease_update_buf;
	std::ifstream fs;
	int start;
	bool end;
	bool is_active;
	int end_count;
	
public:
	UIBase(des::Vec2f _pos, des::Vec2f _size, des::Vec4d _color);
	//
	virtual void update();

	void EaseInApply(std::string start, float end, std::function<float(float, float, float)> ease, float time);
	void EaseOutApply(std::string start, float end, std::function<float(float, float, float)> ease, float time);
	void EaseUpdateApply(std::string start, float end, std::function<float(float, float, float)> ease, float time);
	virtual void EaseCollisionApply(std::string start, float end, std::function<float(float, float, float)> ease, float time) {}


	void EaseUpdate();
	void EaseInUpdate();
	void EaseOutUpdate();

	float* selectUIState(int state);
	


	///////////////////////ゲッター///////////////////////////////
	//コンスト参照にしてないのは動かなかったから
	float getPosX() {
		return pos.x;
	}
	float getPosY() {
		return pos.y;
	}
	float getSizeX() {
		return size.x;
	}
	float getSizeY() {
		return size.y;
	}
	float getColorR() {
		return color.x;
	}
	float getColorG() {
		return color.y;
	}
	float getColorB() {
		return color.z;
	}
	float getColorA() {
		return color.w;
	}

	std::string getTexturePath() {
		return texture_path;
	}
	const bool& isActive() {
		return is_active;
	}
	const bool& NextFlag() {
		return !is_active;
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

	void setTexturePath(std::string path) {
		texture_path = path;
	}
	void setEnd() {
		if (is_active) {
			end = true;
		}
	}
	void Active() {
		is_active = true;
	}
	
	//---------------------------------------------------------


	//CollisionUI
	virtual bool collisionToUI(des::Vec2f _pos) { return false; };
	virtual bool collisionToUI(des::Vec2f _pos, des::Vec2f _size) { return false; };

	//GaugeUI
	virtual float getGaugePosX() { return 0.0f; }
	virtual float getGaugePosY() { return 0.0f; }
	virtual float getGaugeSizeX() { return 0.0f; }
	virtual float getGaugeSizeY() { return 0.0f; }
	virtual std::string getGaugeTexturePath() { return "GaugeUIで定義してください"; }
	virtual bool isGaugeUI() { return false; }

	virtual void setGaugePos(const float& gauge_pos_x, const float& gauge_pos_y) {}
	virtual void setGaugeSize(const float& gauge_size_x, const float& gauge_size_y) {}
	virtual void setGaugeTexturePath(const std::string& path) {}
	//変動する値
	//最大値
	virtual void changeGauge(float value,float max) {}
};


