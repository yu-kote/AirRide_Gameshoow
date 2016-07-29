#include "LeapHands.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include <vector>

LeapHands::LeapHands()
{

}

LeapHands::~LeapHands()
{

}

Leap::HandList & LeapHands::GetHandList() const
{
	return frame.hands();
}

ci::Vec3f LeapHands::GetHandCenterPos() const
{
	if (frame.hands().count() <= 0)
		return ci::Vec3f(0.0f, 0.0f, 0.0f);

	const Leap::HandList &hands = frame.hands();
	Leap::HandList::const_iterator first_hand_itr = hands.begin();
	const Leap::Hand &hand = *first_hand_itr;
	ci::Vec3f hand_center_pos = LeapMotion::toVec3f(hand.palmPosition());
	hand_center_pos.x *= -1.0f;
	hand_center_pos.z *= -1.0f;

	return hand_center_pos;
}

ci::Vec2f LeapHands::GetHandCenterPosToRatio() const
{
	if (frame.hands().count() <= 0)
		return ci::Vec2f(0.0f, 0.0f);

	const Leap::HandList &hands = frame.hands();
	Leap::HandList::const_iterator first_hand_itr = hands.begin();
	const Leap::Hand &hand = *first_hand_itr;
	ci::Vec3f hand_center_pos = LeapMotion::toVec3f(hand.palmPosition());
	
	float ratio_x = ( hand_center_pos.x - virtual_window_center_pos.x ) / virtual_window_size.x / 2.0f;
	float ratio_y = (hand_center_pos.y - virtual_window_center_pos.y) / virtual_window_size.y / 2.0f;

	ratio_x = std::max(-1.0f, ratio_x);
	ratio_x = std::min(1.0f, ratio_x);
	ratio_y = std::max(-1.0f, ratio_y);
	ratio_y = std::min(1.0f, ratio_y);

	/*if (ratio_x > 1.0f)
		ratio_x = 1.0f;
	if (ratio_x < -1.0f)
		ratio_x = -1.0f;
	if (ratio_y > 1.0f)
		ratio_y = 1.0f;
	if (ratio_y < -1.0f)
		ratio_y = -1.0f;*/

	return ci::Vec2f(ratio_x * -1.0f, ratio_y);
}

ci::Vec3f LeapHands::GetHandNormal() const
{
	Leap::HandList &hands = frame.hands();
	Leap::HandList::const_iterator first_hand_itr = hands.begin();
	const Leap::Hand &hand = *first_hand_itr;

	return LeapMotion::toVec3f(hand.palmNormal());
}

ci::Vec2f LeapHands::GetHandNormalToXY() const
{
	Leap::HandList &hands = frame.hands();
	Leap::HandList::const_iterator first_hand_itr = hands.begin();
	const Leap::Hand &hand = *first_hand_itr;

	const ci::Vec3f &hand_normal = LeapMotion::toVec3f(hand.palmNormal());

	return ci::Vec2f(hand_normal.x, hand_normal.y);
}

bool LeapHands::IsHandExist() const
{
	Leap::HandList &hands = frame.hands();

	return (!hands.isEmpty());
}

void LeapHands::Setup()
{
	device = LeapMotion::Device::create();
	device->connectEventHandler(
		[&](Leap::Frame frame)
	{
		this->frame = frame;
	});
}

void LeapHands::Update()
{

}

void LeapHands::Draw()
{
	ci::gl::color(ci::Color(0.0f, 0.0f, 0.0f));

	const Leap::HandList &hands = frame.hands();

	for (Leap::HandList::const_iterator hand_iter = hands.begin();
	hand_iter != hands.end();
		++hand_iter)
	{
		const Leap::Hand &hand = *hand_iter;
		const Leap::Arm &arm = hand.arm();

		ci::Vec3f palm_pos = LeapMotion::toVec3f(hand.palmPosition());
		ci::Vec3f elbow_pos = LeapMotion::toVec3f(arm.elbowPosition());
		ci::Vec3f rotation = ci::Vec3f(hand.direction().pitch(), hand.direction().yaw(), hand.palmNormal().roll());
		ci::Vec3f wrist = LeapMotion::toVec3f(arm.wristPosition());

		ci::gl::drawLine(elbow_pos, wrist);

		std::vector<ci::Vec3f> knuckles;

		const Leap::FingerList fingers = hand.fingers();

		for (Leap::FingerList::const_iterator finger_iter = fingers.begin();
		finger_iter != fingers.end();
			++finger_iter)
		{
			const Leap::Finger &finger = *finger_iter;

			for (int32_t i = 0; i < 4; ++i)
			{
				const Leap::Bone &bone = finger.bone(static_cast<Leap::Bone::Type>(i));
				ci::Vec3f center = LeapMotion::toVec3f(bone.center());
				ci::Vec3f direction = LeapMotion::toVec3f(bone.direction());
				ci::Vec3f start = center - direction * bone.length() * 0.5f;
				ci::Vec3f end = center + direction * bone.length() * 0.5f;

				if (i == 0)
				{
					knuckles.push_back(start);
					ci::gl::drawLine(wrist, start);
				}
				else
				{
					ci::gl::drawLine(start, end);
				}
			}
		}

		if (knuckles.size() > 1)
		{
			for (size_t i = 1; i < knuckles.size(); ++i)
			{
				const ci::Vec3f &v0 = knuckles.at(i - 1);
				const ci::Vec3f v1 = knuckles.at(i);
				ci::gl::drawLine(v0, v1);
			}
			ci::gl::drawLine(elbow_pos, knuckles.at(0));
		}
	}
}
