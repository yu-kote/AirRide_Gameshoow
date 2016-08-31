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
		return &color.x;
		break;
	case 5:
		return &color.y;
		break;
	case 6:
		return &color.z;
		break;
	case 7:
		return &color.w;
		break;
	}
	return reinterpret_cast<float*>(&pos.x);
}

UIBase::UIBase(des::Vec2f _pos, des::Vec2f _size, des::Vec4d _color)
	: pos(_pos), size(_size), color(_color) {
	fncPushBack(easing_function);
	is_active = false;
	start = 0;
	end = false;
	end_count = 0;
	own_ui = UITYPE::NormalUI;
}

void UIBase::update() {
	if (is_active) {
		EaseInUpdate();
		EaseOutUpdate();
		EaseUpdate();
	}
}

void UIBase::EaseInApply(std::string start, float end, std::function<float(float, float, float)> ease, float time)
{
	ease_in_buf.push_back(EasingBuf(start, end, ease, time));
}

void UIBase::EaseOutApply(std::string start, float end, std::function<float(float, float, float)> ease, float time)
{
	ease_end_buf.push_back(EasingBuf(start, end, ease, time));
}

void UIBase::EaseUpdateApply(std::string start, float end, std::function<float(float, float, float)> ease, float time)
{
	ease_update_buf.push_back(EasingBuf(start, end, ease, time));
}

void UIBase::EaseUpdate()
{
	if (c_Easing::isEnd(pos.x)) {
		for (int i = 0; i != ease_update_buf.size(); i++) {
			c_Easing::apply(*selectUIState(UIState::get()[ease_update_buf[i].start]),
				ease_update_buf[i].end, ease_update_buf[i].ease, ease_update_buf[i].time);
		}
	}
}

void UIBase::EaseInUpdate()
{
	start++;
	if (start == 1) {
		for (int i = 0; i != ease_in_buf.size(); i++) {
			c_Easing::apply(*selectUIState(UIState::get()[ease_in_buf[i].start]),
				ease_in_buf[i].end, ease_in_buf[i].ease, ease_in_buf[i].time);
		}
	}
}

void UIBase::EaseOutUpdate()
{
	if (end) {
		end_count++;
		if (end_count == 1) {
			for (int i = 0; i != ease_in_buf.size(); i++) {
				c_Easing::clear(*selectUIState(UIState::get()[ease_in_buf[i].start]));
			}
			for (int i = 0; i != ease_update_buf.size(); i++) {
				c_Easing::clear(*selectUIState(UIState::get()[ease_update_buf[i].start]));
			}
			for (int i = 0; i != ease_end_buf.size(); i++) {
				c_Easing::apply(*selectUIState(UIState::get()[ease_end_buf[i].start]),
					ease_end_buf[i].end, ease_end_buf[i].ease, ease_end_buf[i].time);
			}
			
		}
		for(int i = 0; i != ease_end_buf.size(); i++) {
			if (c_Easing::isEnd(*selectUIState(UIState::get()[ease_end_buf[i].start]))) {
				is_active = false;
				start = 0;
				end_count = 0;
				end = false;
			}
		}
	}

}

