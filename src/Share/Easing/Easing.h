#pragma once
#include <math.h>
#include <unordered_map>
#include "cinder/CinderMath.h"

struct c_Easinginfo
{
	c_Easinginfo(float _begincount, float _endcoount, float _beginpos, float _endpos, std::function<float(float, float, float)> _func) {
		func = _func;
		begincount = _begincount;
		endcoount = _endcoount;
		beginpos = _beginpos;
		endpos = _endpos;
	};
	std::function<float(float, float, float)> func;
	float begincount;
	float endcoount;
	float beginpos;
	float endpos;
};


class c_AnimInfo
{
	c_AnimInfo() {
		count = 0;
		is_active = true;
	}
	void apply(float _begincount, float _endcoount, float _beginpos, float _endpos, std::function<float(float, float, float)> _func) {
		info.push_back(c_Easinginfo(_begincount, _endcoount, _beginpos, _endpos, _func));
	}
	void countIncrement() {
		if (is_active) {
			count++;
			//info
		}
	}


	std::vector<c_Easinginfo> info;
	int count;
	bool is_active;
};

class c_Easing
{
public:
	static void apply() {

	}
private:
	static std::unordered_map <float*, c_AnimInfo>  easinginfo;
};
class EasingFunction {
public:
	static float Linear(float t, float b, float e) {
		return (e - b) * t + b;
	}
	static float BackIn(float t, float b, float e) {
		float s = 1.70158f;
		return (e - b) * t * t * ((s + 1) * t - s) + b;
	}
	static float BackOut(float t, float b, float e) {
		float s = 1.70158f;
		t -= 1.0;
		return (e - b) * (t * t * ((s + 1) * t + s) + 1) + b;
	}
	static float BackInOut(float t, float b, float e) {
		float s = 1.70158f * 1.525f;
		if ((t /= 0.5) < 1) return (e - b) / 2 * (t * t * ((s + 1) * t - s)) + b;
		t -= 2;
		return (e - b) / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
	}
	static float BounceOut(float t, float b, float e) {
		if (t < (1 / 2.75f)) {
			return (e - b) * (7.5625f * t * t) + b;
		}
		else if (t < (2 / 2.75f)) {
			t -= (1.5f / 2.75f);
			return (e - b) * (7.5625f * t * t + 0.75f) + b;
		}
		else if (t < (2.5 / 2.75)) {
			t -= (2.25f / 2.75f);
			return (e - b) * (7.5625f * t * t + 0.9375) + b;
		}
		else {
			t -= (2.625f / 2.75f);
			return (e - b) * (7.5625 * t * t + 0.984375) + b;
		}
	}
	static  float BounceIn(float t, float b, float e) {
		return (e - b) - BounceOut(1.0 - t, 0, e - b) + b;
	}
	static float BounceInOut(float t, float b, float e) {
		if (t < 0.5) return BounceIn(t * 2, 0, e - b) * 0.5 + b;
		else         return BounceOut(t * 2 - 1.0, 0, e - b) * 0.5 + (e - b) * 0.5 + b;
	}
	static float CircIn(float t, float b, float e) {
		return -(e - b) * (std::sqrt(1 - t * t) - 1) + b;
	}
	static float CircOut(float t, float b, float e) {
		t -= 1.0;
		return (e - b) * std::sqrt(1 - t * t) + b;
	}
	static float CircInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return -(e - b) / 2 * (std::sqrt(1 - t * t) - 1) + b;
		t -= 2;
		return (e - b) / 2 * (std::sqrt(1 - t * t) + 1) + b;
	}
	static float CubicIn(float t, float b, float e) {
		return (e - b) * t * t * t + b;
	}
	static float CubicOut(float t, float b, float e) {
		t -= 1.0;
		return (e - b) * (t * t * t + 1) + b;
	}
	static float CubicInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t + b;
		t -= 2;
		return (e - b) / 2 * (t * t * t + 2) + b;
	}
	static float ElasticIn(float t, float b, float e) {
		if (t == 0) return b;
		if (t == 1) return e;

		float p = 0.3f;
		float a = e - b;
		float s = p / 4;
		t -= 1;
		return -(a * std::pow(2, 10 * t) * std::sin((t - s) * (2 * M_PI) / p)) + b;
	}
	static float ElasticOut(float t, float b, float e) {
		if (t == 0) return b;
		if (t == 1) return e;

		float p = 0.3f;
		float a = e - b;
		float s = p / 4;
		return (a * std::pow(2, -10 * t) * std::sin((t - s) * (2 * M_PI) / p) + a + b);
	}
	static float ElasticInOut(float t, float b, float e) {
		if (t == 0) return b;
		if ((t /= 0.5) == 2) return e;

		float p = 0.3f * 1.5f;
		float a = e - b;
		float s = p / 4;
		if (t < 1) {
			t -= 1;
			return -0.5 * (a * std::pow(2, 10 * t) * std::sin((t - s) * (2 * M_PI) / p)) + b;
		}
		t -= 1;
		return a * std::pow(2, -10 * t) * std::sin((t - s) * (2 * M_PI) / p) * 0.5 + a + b;
	}
	static float ExpoIn(float t, float b, float e) {
		return (t == 0) ? b : (e - b) * std::pow(2, 10 * (t - 1)) + b;
	}
	static float ExpoOut(float t, float b, float e) {
		return (t == 1) ? e : (e - b) * (-std::pow(2, -10 * t) + 1) + b;
	}
	static float ExpoInOut(float t, float b, float e) {
		if (t == 0) return b;
		if (t == 1) return e;
		if ((t /= 0.5) < 1) return (e - b) / 2 * std::pow(2, 10 * (t - 1)) + b;
		return (e - b) / 2 * (-std::pow(2, -10 * --t) + 2) + b;
	}
	static float QuadIn(float t, float b, float e) {
		return (e - b) * t * t + b;
	}
	static float QuadOut(float t, float b, float e) {
		return -(e - b) * t * (t - 2) + b;
	}
	static float QuadInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return (e - b) / 2 * t * t + b;
		--t;
		return -(e - b) / 2 * (t * (t - 2) - 1) + b;
	}
	static float QuartIn(float t, float b, float e) {
		return (e - b) * t * t * t * t + b;
	}
	static float QuartOut(float t, float b, float e) {
		t -= 1.0;
		return -(e - b) * (t * t * t * t - 1) + b;
	}
	static float QuartInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t * t + b;
		t -= 2;
		return -(e - b) / 2 * (t * t * t * t - 2) + b;
	}
	static float QuintIn(float t, float b, float e) {
		return (e - b) * t * t * t * t * t + b;
	}
	static float QuintOut(float t, float b, float e) {
		t -= 1.0;
		return (e - b) * (t * t * t * t * t + 1) + b;
	}
	static float QuintInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t * t * t + b;
		t -= 2;
		return (e - b) / 2 * (t * t * t * t * t + 2) + b;
	}
	static float SineIn(float t, float b, float e) {
		return -(e - b) * std::cos(t * (M_PI / 2)) + (e - b) + b;
	}
	static float SineOut(float t, float b, float e) {
		return (e - b) * std::sin(t * (M_PI / 2)) + b;
	}
	static float SineInOut(float t, float b, float e) {
		return -(e - b) / 2 * (std::cos(M_PI * t) - 1) + b;
	}
};