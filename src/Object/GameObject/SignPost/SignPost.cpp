#include "SignPost.h"

using namespace ci;
using namespace ci::app;




ar::SignPost::SignPost(ci::Vec3f _pos)
{
	pos = _pos;
	matrix = Matrix44f::identity();
}

void ar::SignPost::setDirection(ci::Vec3f _nextpos)
{
	direction = _nextpos -pos;
	ci::Vec2f rotate;
	rotate.y = atan2(direction.x, direction.z);
	rotate.x = atan2(ci::Vec2f(direction.x, direction.z).length(), direction.y) - M_PI / 2;

	matrix *= ci::Matrix44f::createRotation(ci::Vec3f(0, rotate.y, 0.f));
	matrix *= ci::Matrix44f::createRotation(ci::Vec3f(rotate.x, 0, 0.f));

}

void ar::SignPost::setRingQuat(ci::Vec3f _prevpos)
{
	ring_quat = Quatf(Vec3f::zAxis(),
		((pos - _prevpos).normalized()
			+ direction.normalized()).normalized());
	
}

void ar::SignPost::setLength(float _length)
{
	length = _length;
}

float ar::SignPost::getLength()
{
	return length;
}

ci::Vec3f ar::SignPost::getDirection()
{
	return direction;
}

ci::Matrix44f ar::SignPost::getMatrix()
{
	return matrix;
}

ci::Vec3f ar::SignPost::getPos()
{
	return pos;
}

void ar::SignPost::draw()
{
#if 0
	gl::pushModelView();

	gl::translate(pos);
	gl::drawCube(Vec3f::zero(),Vec3f::one()*0.1f);
	gl::drawVector(Vec3f::zero(), direction);
	gl::popModelView();
	


	//gl::drawCube(transform.position,transform.scale);

#endif // DEBUG
}

void ar::SignPost::ringDraw()
{
	gl::pushModelView();
	gl::translate(pos);
	gl::multModelView(ring_quat.toMatrix44());
	gl::drawTorus(7.0f, 0.3f, 1, 1);
	gl::popModelView();

}
