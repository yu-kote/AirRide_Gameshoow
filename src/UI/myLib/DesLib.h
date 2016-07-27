#pragma once

#include <cmath>
#include <cstring>
#include <iostream>
#include <cassert>
#include <limits>
namespace des {
	template<typename T> class Vec3;

template<typename T>
class Vec2
{
public:
	T x, y;

	typedef T							TYPE;
	typedef T							value_type;

	static const int DIM = 2;

	Vec2() :x(0), y(0) {}
	Vec2(T nx, T ny) : x(nx), y(ny) {}
	Vec2(const Vec2<T>& src) : x(src.x), y(src.y) {}
	explicit Vec2(const T *d) : x(d[0]), y(d[1]) {}

	template<typename FromT>
	Vec2(const Vec2<FromT>& src)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
	{}

	void set(T ax, T ay)
	{
		x = ax; y = ay;
	}

	void set(const Vec2<T> &rhs)
	{
		x = rhs.x; y = rhs.y;
	}

	// Operators
	template<typename FromT>
	Vec2<T>& operator=(const Vec2<FromT>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		return *this;
	}

	Vec2<T>& operator=(const Vec2<T>& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	T& operator[](int n)
	{
		assert(n >= 0 && n <= 1);
		return (&x)[n];
	}

	const T& operator[](int n) const
	{
		assert(n >= 0 && n <= 1);
		return (&x)[n];
	}

	T*	ptr() const { return &(const_cast<Vec2*>(this)->x); }

	const Vec2<T>	operator+(const Vec2<T>& rhs) const { return Vec2<T>(x + rhs.x, y + rhs.y); }
	const Vec2<T>	operator-(const Vec2<T>& rhs) const { return Vec2<T>(x - rhs.x, y - rhs.y); }
	const Vec2<T>	operator*(const Vec2<T>& rhs) const { return Vec2<T>(x * rhs.x, y * rhs.y); }
	const Vec2<T>	operator/(const Vec2<T>& rhs) const { return Vec2<T>(x / rhs.x, y / rhs.y); }
	Vec2<T>&	operator+=(const Vec2<T>& rhs) { x += rhs.x; y += rhs.y; return *this; }
	Vec2<T>&	operator-=(const Vec2<T>& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	Vec2<T>&	operator*=(const Vec2<T>& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
	Vec2<T>&	operator/=(const Vec2<T>& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
	const Vec2<T>	operator/(T rhs) const { return Vec2<T>(x / rhs, y / rhs); }
	Vec2<T>&	operator+=(T rhs) { x += rhs;	y += rhs; return *this; }
	Vec2<T>&	operator-=(T rhs) { x -= rhs; y -= rhs; return *this; }
	Vec2<T>&	operator*=(T rhs) { x *= rhs; y *= rhs; return *this; }
	Vec2<T>&	operator/=(T rhs) { x /= rhs; y /= rhs; return *this; }

	Vec2<T>		operator-() const { return Vec2<T>(-x, -y); } // unary negation

	bool operator==(const Vec2<T> &rhs) const
	{
		return (x == rhs.x) && (y == rhs.y);
	}

	bool operator!=(const Vec2<T> &rhs) const
	{
		return !(*this == rhs);
	}

	T dot(const Vec2<T> &rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	//! Returns the z component of the cross if the two operands were Vec3's on the XY plane, the equivalent of Vec3(*this).cross( Vec3(rhs) ).z
	T cross(const Vec2<T> &rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}



	T distanceSquared(const Vec2<T> &rhs) const
	{
		return (*this - rhs).lengthSquared();
	}



	void normalize()
	{
		DIST invS = 1 / length();
		x *= invS;
		y *= invS;
	}

	Vec2<T> normalized() const
	{
		DIST invS = 1 / length();
		return Vec2<T>(x * invS, y * invS);
	}

	// tests for zero-length
	void safeNormalize()
	{
		T s = lengthSquared();
		if (s > 0) {
			DIST invL = 1 / math<DIST>::sqrt(s);
			x *= invL;
			y *= invL;
		}
	}

	Vec2<T> safeNormalized() const
	{
		T s = lengthSquared();
		if (s > 0) {
			DIST invL = 1 / math<DIST>::sqrt(s);
			return Vec2<T>(x * invL, y * invL);
		}
		else
			return Vec2<T>::zero();
	}



	T lengthSquared() const
	{
		return x * x + y * y;
	}



	//! Returns a copy of the Vec2 with its length limited to \a maxLength, scaling it proportionally if necessary.
	Vec2<T> limited(T maxLength) const
	{
		T lengthSquared = x * x + y * y;

		if ((lengthSquared > maxLength * maxLength) && (lengthSquared > 0)) {
			DIST ratio = maxLength / math<DIST>::sqrt(lengthSquared);
			return Vec2<T>(x * ratio, y * ratio);
		}
		else
			return *this;
	}

	void invert()
	{
		x = -x;
		y = -y;
	}

	Vec2<T> inverse() const
	{
		return Vec2<T>(-x, -y);
	}

	Vec2<T> lerp(T fact, const Vec2<T>& r) const
	{
		return (*this) + (r - (*this)) * fact;
	}

	void lerpEq(T fact, const Vec2<T> &rhs)
	{
		x = x + (rhs.x - x) * fact; y = y + (rhs.y - y) * fact;
	}

	// GLSL inspired swizzling functions.
	Vec2<T> xx() const { return Vec2<T>(x, x); }
	Vec2<T> xy() const { return Vec2<T>(x, y); }
	Vec2<T> yx() const { return Vec2<T>(y, x); }
	Vec2<T> yy() const { return Vec2<T>(y, y); }

	Vec3<T> xxx() const { return Vec3<T>(x, x, x); }
	Vec3<T> xxy() const { return Vec3<T>(x, x, y); }
	Vec3<T> xyx() const { return Vec3<T>(x, y, x); }
	Vec3<T> xyy() const { return Vec3<T>(x, y, y); }
	Vec3<T> yxx() const { return Vec3<T>(y, x, x); }
	Vec3<T> yxy() const { return Vec3<T>(y, x, y); }
	Vec3<T> yyx() const { return Vec3<T>(y, y, x); }
	Vec3<T> yyy() const { return Vec3<T>(y, y, y); }

	static Vec2<T> max()
	{
		return Vec2<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
	}

	static Vec2<T> zero()
	{
		return Vec2<T>(0, 0);
	}

	static Vec2<T> one()
	{
		return Vec2<T>(1, 1);
	}

	friend std::ostream& operator<<(std::ostream& lhs, const Vec2<T>& rhs)
	{
		lhs << "[" << rhs.x << "," << rhs.y << "]";
		return lhs;
	}

	static Vec2<T> xAxis() { return Vec2<T>(1, 0); }
	static Vec2<T> yAxis() { return Vec2<T>(0, 1); }

	static Vec2<T> NaN() { return Vec2<T>(math<T>::NaN(), math<T>::NaN()); }
	
};

typedef Vec2<int>		Vec2i;
typedef Vec2<float>		Vec2f;
typedef Vec2<double>	Vec2d;


//void tasingLinear(Vec2d& begin_pos, Vec2d end_pos, float t) {
//	begin_pos = Vec2d((end_pos.x - begin_pos.x) * t + begin_pos.x, (end_pos.y - begin_pos.y) * t + begin_pos.y);
//}


//void tasingBackIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	float s = 1.70158;
//	return (e - b) * t * t * ((s + 1) * t - s) + b;
//}
//
//void tasingBackOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	float s = 1.70158;
//	t -= 1.0;
//	return (e - b) * (t * t * ((s + 1) * t + s) + 1) + b;
//}
//
//void tasingBackInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	float s = 1.70158 * 1.525;
//	if ((t /= 0.5) < 1) return (e - b) / 2 * (t * t * ((s + 1) * t - s)) + b;
//	t -= 2;
//	return (e - b) / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
//}
//
//
//void tasingBounceOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if (t < (1 / 2.75)) {
//		return (e - b) * (7.5625 * t * t) + b;
//	}
//	else if (t < (2 / 2.75)) {
//		t -= (1.5 / 2.75);
//		return (e - b) * (7.5625 * t * t + 0.75) + b;
//	}
//	else if (t < (2.5 / 2.75)) {
//		t -= (2.25 / 2.75);
//		return (e - b) * (7.5625 * t * t + 0.9375) + b;
//	}
//	else {
//		t -= (2.625 / 2.75);
//		return (e - b) * (7.5625 * t * t + 0.984375) + b;
//	}
//}
//
//void tasingBounceIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return (e - b) - EasingBounceOut(1.0 - t, 0, e - b) + b;
//}
//
//void tasingBounceInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if (t < 0.5) return EasingBounceIn(t * 2, 0, e - b) * 0.5 + b;
//	else         return EasingBounceOut(t * 2 - 1.0, 0, e - b) * 0.5 + (e - b) * 0.5 + b;
//}
//
//
//void tasingCircIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return -(e - b) * (std::sqrt(1 - t * t) - 1) + b;
//}
//
//void tasingCircOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	t -= 1.0;
//	return (e - b) * std::sqrt(1 - t * t) + b;
//}
//
//void tasingCircInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if ((t /= 0.5) < 1) return -(e - b) / 2 * (std::sqrt(1 - t * t) - 1) + b;
//	t -= 2;
//	return (e - b) / 2 * (std::sqrt(1 - t * t) + 1) + b;
//}
//
//
//void tasingCubicIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return (e - b) * t * t * t + b;
//}
//
//void tasingCubicOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	t -= 1.0;
//	return (e - b) * (t * t * t + 1) + b;
//}
//
//void tasingCubicInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t + b;
//	t -= 2;
//	return (e - b) / 2 * (t * t * t + 2) + b;
//}
//
//
//void tasingElasticIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if (t == 0) return b;
//	if (t == 1) return e;
//
//	float p = 0.3;
//	float a = e - b;
//	float s = p / 4;
//	t -= 1;
//	return -(a * std::pow(2, 10 * t) * std::sin((t - s) * (2 * M_PI) / p)) + b;
//}
//
//void tasingElasticOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if (t == 0) return b;
//	if (t == 1) return e;
//
//	float p = 0.3;
//	float a = e - b;
//	float s = p / 4;
//	return (a * std::pow(2, -10 * t) * std::sin((t - s) * (2 * M_PI) / p) + a + b);
//}
//
//void tasingElasticInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if (t == 0) return b;
//	if ((t /= 0.5) == 2) return e;
//
//	float p = 0.3 * 1.5;
//	float a = e - b;
//	float s = p / 4;
//	if (t < 1) {
//		t -= 1;
//		return -0.5 * (a * std::pow(2, 10 * t) * std::sin((t - s) * (2 * M_PI) / p)) + b;
//	}
//	t -= 1;
//	return a * std::pow(2, -10 * t) * std::sin((t - s) * (2 * M_PI) / p) * 0.5 + a + b;
//}
//
//
//void tasingExpoIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return (t == 0) ? b : (e - b) * std::pow(2, 10 * (t - 1)) + b;
//}
//
//void tasingExpoOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return (t == 1) ? e : (e - b) * (-std::pow(2, -10 * t) + 1) + b;
//}
//
//void tasingExpoInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if (t == 0) return b;
//	if (t == 1) return e;
//	if ((t /= 0.5) < 1) return (e - b) / 2 * std::pow(2, 10 * (t - 1)) + b;
//	return (e - b) / 2 * (-std::pow(2, -10 * --t) + 2) + b;
//}
//
//
//void tasingQuadIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return (e - b) * t * t + b;
//}
//
//void tasingQuadOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return -(e - b) * t * (t - 2) + b;
//}
//
//void tasingQuadInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if ((t /= 0.5) < 1) return (e - b) / 2 * t * t + b;
//	--t;
//	return -(e - b) / 2 * (t * (t - 2) - 1) + b;
//}
//
//
//void tasingQuartIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return (e - b) * t * t * t * t + b;
//}
//
//void tasingQuartOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	t -= 1.0;
//	return -(e - b) * (t * t * t * t - 1) + b;
//}
//
//void tasingQuartInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t * t + b;
//	t -= 2;
//	return -(e - b) / 2 * (t * t * t * t - 2) + b;
//}
//
//
//void tasingQuintIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return (e - b) * t * t * t * t * t + b;
//}
//
//void tasingQuintOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	t -= 1.0;
//	return (e - b) * (t * t * t * t * t + 1) + b;
//}
//
//void tasingQuintInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t * t * t + b;
//	t -= 2;
//	return (e - b) / 2 * (t * t * t * t * t + 2) + b;
//}
//
//
//void tasingSineIn(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return -(e - b) * std::cos(t * (M_PI / 2)) + (e - b) + b;
//}
//
//void tasingSineOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return (e - b) * std::sin(t * (M_PI / 2)) + b;
//}
//
//void tasingSineInOut(Vec2f& begin_pos, Vec2f end_pos, float t) {
//	return -(e - b) / 2 * (std::cos(M_PI * t) - 1) + b;
//}
//
//









}