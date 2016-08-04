#include "SignPost.h"

using namespace ci;
using namespace ci::app;


ar::SignPost::SignPost()
{
}

ar::SignPost::SignPost(ci::Vec3f position_, ci::Vec3f size_)
{
	transform.position = position_;
	transform.scale = size_;
	direction = ci::Vec3f::zAxis();
	length = 0;
	setup();
}
ar::SignPost::SignPost(ci::Vec3f position_, ci::Vec3f _direction, ci::Vec3f size_)
{
	transform.position = position_;
	transform.scale = size_;
	direction = _direction;
	length = 0;
	setup();

}
void ar::SignPost::setup()
{
}

void ar::SignPost::update()
{
}

void ar::SignPost::draw()
{
#if 1

	//gl::drawCube(transform.position,transform.scale);

#endif // DEBUG
}
