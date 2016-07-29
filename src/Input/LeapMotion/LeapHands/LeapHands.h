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
	//���̒��S���W��Ԃ�
	//����͎g��Ȃ�
	ci::Vec3f GetHandCenterPos() const;
	//���z�ŉ�ʂ���菶�̒��S���W���ŕԂ�
	//-1.0f ~ 1.0f
	ci::Vec2f GetHandCenterPosToRatio() const;
	//���̖@����Ԃ�
	ci::Vec3f GetHandNormal() const;
	//���̖@���𕪉�����xy���ɑ΂���l��Ԃ�
	ci::Vec2f GetHandNormalToXY() const;
	//�����ݎ肪�����Ȃ�����Ԃ�
	bool IsHandExist() const;

	void Setup();
	void Update();
	void Draw();
};