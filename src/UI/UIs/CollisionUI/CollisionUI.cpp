#include "CollisionUI.h"



void CollisionUI::animation()
{
}

void CollisionUI::update()
{
	if (is_active) {
		EaseInUpdate();
		
	    EaseOutUpdate();

		EaseUpdate();

		EaseCollisionUpdate();
	}
}

bool CollisionUI::collisionToUI(des::Vec2f _pos)
{

	if (des::collisionPlateToPoint(pos, size, _pos)) {
		for (int i = 0; i != ease_collision_buf.size(); i++) {
			c_Easing::apply(*selectUIState(UIState::get()[ease_collision_buf[i].start]),
				ease_collision_buf[i].end, ease_collision_buf[i].ease, ease_collision_buf[i].time);
		}
		return true;
	}
	return false;
}

bool CollisionUI::collisionToUI(des::Vec2f _pos, des::Vec2f _size)
{
	if (des::collisionPlateToPlate(pos, size, _pos, _size)) {
		for (int i = 0; i != ease_collision_buf.size(); i++) {
			c_Easing::apply(*selectUIState(UIState::get()[ease_collision_buf[i].start]),
				ease_collision_buf[i].end, ease_collision_buf[i].ease, ease_collision_buf[i].time);
		}
		return true;
	}
	return false;
}

void CollisionUI::EaseCollisionApply(std::string start, float end, std::function<float(float, float, float)> ease, float time)
{
	ease_collision_buf.push_back(EasingBuf(start, end, ease, time));
}

void CollisionUI::EaseCollisionUpdate()
{


}