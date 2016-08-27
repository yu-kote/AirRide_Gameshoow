#include "Share.h"

bool sphereToSphere(ci::Vec3f pos1_, float radius1_, ci::Vec3f pos2_, float radius2_)
{
	float x = (pos2_.x - pos1_.x) * (pos2_.x - pos1_.x);
	float y = (pos2_.y - pos1_.y) * (pos2_.y - pos1_.y);
	float z = (pos2_.z - pos1_.z) * (pos2_.z - pos1_.z);
	float total = x + y + z;

	float r = (radius1_ + radius2_) * (radius1_ + radius2_);
	return total <= r;
	/*float dis = pos1_.distanceSquared(pos2_);
	float r = (radius1_ + radius2_) * (radius1_ + radius2_);
	return dis <= r;*/
}