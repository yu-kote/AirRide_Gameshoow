#pragma once
#include"../../UIBase.h"

class GaugeUI : public UIBase
{
private:
	des::Vec2f gauge_pos;
	des::Vec2f gauge_size;
	std::string gauge_texture_path;
	bool gauge_max;
	float gauge_max_x;
public:
	GaugeUI(des::Vec2f _pos, des::Vec2f _size, des::Vec4d _color) :UIBase(_pos, _size, _color) { gauge_max == false; };
	void update() {};
	bool isGaugeUI() { return true; }
	float getGaugePosX() {
		return gauge_pos.x;
	}
	float getGaugePosY() {
		return gauge_pos.y;
	}
	float getGaugeSizeX() {
		return gauge_size.x;
	}
	float getGaugeSizeY() {
		return gauge_size.y;
	}
	std::string getGaugeTexturePath() {
		return gauge_texture_path;
	}

	void setGaugePos(const float& gauge_pos_x, const float& gauge_pos_y) {
		gauge_pos.x = gauge_pos_x;
		gauge_pos.y = gauge_pos_y;
	}
	void setGaugeSize(const float& gauge_size_x, const float& gauge_size_y) {
		gauge_size.x = gauge_size_x;
		gauge_size.y = gauge_size_y;
		gauge_max_x = gauge_size_x;
	}
	void setGaugeTexturePath(const std::string& path) {
		gauge_texture_path = path;
	}
	//•Ï“®‚·‚é’l
	//Å‘å’l
	void changeGauge(float value,float max);
};