#include "UIBase.h"
void fncPushBack(std::vector<std::function<float(float, float, float)>> fnc) {
	fnc.push_back(EasingFunction::BackIn);
	fnc.push_back(EasingFunction::BackInOut);
	fnc.push_back(EasingFunction::BackOut);
	fnc.push_back(EasingFunction::BounceIn);
	fnc.push_back(EasingFunction::BounceInOut);
	fnc.push_back(EasingFunction::BounceOut);
	fnc.push_back(EasingFunction::CircIn);
	fnc.push_back(EasingFunction::CircInOut);
	fnc.push_back(EasingFunction::CircOut);
	fnc.push_back(EasingFunction::CubicIn);
	fnc.push_back(EasingFunction::CubicInOut);
	fnc.push_back(EasingFunction::CubicOut);
	fnc.push_back(EasingFunction::ElasticIn);
	fnc.push_back(EasingFunction::ElasticInOut);
	fnc.push_back(EasingFunction::ElasticOut);
	fnc.push_back(EasingFunction::ExpoIn);
	fnc.push_back(EasingFunction::ExpoInOut);
	fnc.push_back(EasingFunction::ExpoOut);
	fnc.push_back(EasingFunction::Linear);
	fnc.push_back(EasingFunction::QuadIn);
	fnc.push_back(EasingFunction::QuadInOut);
	fnc.push_back(EasingFunction::QuadOut);
	fnc.push_back(EasingFunction::QuartIn);
	fnc.push_back(EasingFunction::QuartInOut);
	fnc.push_back(EasingFunction::QuadOut);
	fnc.push_back(EasingFunction::QuintIn);
	fnc.push_back(EasingFunction::QuintInOut);
	fnc.push_back(EasingFunction::QuintOut);
	fnc.push_back(EasingFunction::SineIn);
	fnc.push_back(EasingFunction::SineInOut);
	fnc.push_back(EasingFunction::SineOut);
}

float* UIBase::selectUIState(int state)
{
	switch (state)
	{
	case 0:
		return &pos.x;
		break;
	case 1:
		return &pos.y;
		break;
	case 2:
		return &size.x;
		break;
	case 3:
		return &size.y;
		break;
	case 4:
		return reinterpret_cast<float*>(&color.x);
		break;
	case 5:
		return reinterpret_cast<float*>(&color.y);
		break;
	case 6:
		return reinterpret_cast<float*>(&color.z);
		break;
	case 7:
		return reinterpret_cast<float*>(&color.w);
		break;
	}
	return reinterpret_cast<float*>(&pos.x);
}



UIBase::UIBase(des::Vec2f _pos, des::Vec2f _size, des::Vec4d _color)
	: pos(_pos), size(_size), color(_color) {
	fncPushBack(easing_function);
	start = false;
	end = false;
}

void UIBase::easingUpdate() {
}

void UIBase::EaseInApply(std::string s, float e, std::function<float(float, float, float)> ease, float time)
{
	c_Easing::apply(*selectUIState(UIState::get()[s]),e,ease,time);
}

