#pragma once
#include "../Cinder-LeapMotion.h"

#define LEAPHANDS LeapHands::Get()


class LeapHands
{
private:

	LeapMotion::DeviceRef device;
	Leap::Frame frame;

	const ci::Vec2f virtual_window_center_pos = ci::Vec2f(0.0f, 320.0f);
	const ci::Vec2f virtual_window_size = ci::Vec2f(460.0f, 480.0f);

public:

	LeapHands();
	~LeapHands();

	static LeapHands& Get()
	{
		static LeapHands leap_hands;

		return leap_hands;
	}

	Leap::HandList& GetHandList() const;
	//掌の中心座標を返す
	//今回は使わない
	ci::Vec3f GetHandCenterPos() const;
	//仮想で画面を作り掌の中心座標を比で返す
	//-1.0f ~ 1.0f
	ci::Vec2f GetHandCenterPosToRatio() const;
	// 左上原点
	ci::Vec2f GetHandCenterPosToRatioLeftUp() const;
	//掌の法線を返す
	ci::Vec3f GetHandNormal() const;
	//掌の法線を分解してxy軸に対する値を返す
	ci::Vec2f GetHandNormalToXY() const;
	//今現在手が歩かないかを返す
	bool IsHandExist() const;

	void Setup();
	void Update();
	void Draw();
};