#include "Camera.h"
#include "../../../Share/Share.h"
#include "../../../Input/InputEvent.h"
#include "../../../Share/Resize.h"
#include "CameraPosition.h"
#include <random>

using namespace ci;
using namespace ci::app;

ar::Camera::Camera()
{
}

void ar::Camera::setup()
{
	camera = CameraPersp(WIDTH, HEIGHT,
						 60.0f,
						 1.0f, 1000.0f);
	lookpoint = Vec3f(1, 1, 1);
	Vec3f camera_pos = chara->getMatrix()
		* Matrix44f::createTranslation(
			Vec3f(chara->transform.position.x, chara->transform.position.y, 0)).inverted()
		*Vec3f::zero();
	Vec3f dir = -chara->getMatrix().transformVec(Vec3f::zAxis());
	camera.setEyePoint(camera_pos + dir * 10);
	camera.setCenterOfInterestPoint(camera_pos);
	camera_run = true;
	Params->addParam("camera_run", &camera_run);

	camera.setAspectRatio(getWindowAspectRatio());

	shake_count = 0;
}

void ar::Camera::update()
{
	ResizeGet.setPerspCameraResize = [&]()
	{
		camera.setAspectRatio(getWindowAspectRatio());
	};

	if (camera_run) {
		Vec3f camera_pos = chara->getMatrix()
			* Matrix44f::createTranslation(
				Vec3f(chara->transform.position.x, chara->transform.position.y, 0)).inverted()
			*Vec3f::zero();
		Vec3f dir = -chara->getMatrix().transformVec(Vec3f::zAxis());
		setEyePoint(camera_pos + dir * 10);
		setCenterOfInterestPoint(camera_pos);

	}

	else {
		moveUpdate();
		rotateUpdate();
		cameraDecision(transform.position,
					   lookpoint);
	}

	shakeCameraUpdate();
	gl::setMatrices(camera);

	CameraPosition = camera.getEyePoint();
}

void ar::Camera::draw()
{
}

void ar::Camera::setEyePoint(ci::Vec3f _pos)
{
	camera.setEyePoint(camera.getEyePoint() +
					   ((_pos - camera.getEyePoint()) * 0.1f));
	//camera.setEyePoint(_pos);
}

void ar::Camera::setCenterOfInterestPoint(ci::Vec3f _pos)
{
	/*camera.setCenterOfInterestPoint(
		camera.getCenterOfInterestPoint() +
		((_pos - camera.getEyePoint()) * 0.1f));*/
	camera.setCenterOfInterestPoint(_pos);
	shake_buf = _pos;
}

void ar::Camera::setChara(std::shared_ptr<CharaBase> _chara)
{
	chara = _chara.get();
}

ci::Vec3f ar::Camera::getCenterOfInterestPoint()
{
	return camera.getEyePoint();
}

void ar::Camera::cameraDecision(const ci::Vec3f & position_, const ci::Vec3f & lookpoint_)
{
	gl::pushModelView();
	camera.setEyePoint(position_ + move_distance);
	camera.setCenterOfInterestPoint(lookpoint_ + move_distance);
	gl::popModelView();
}

void ar::Camera::moveUpdate(int invert_)
{
	Vec3f vec = Vec3f::zero();
	const float speed = 0.2f;

	inputVector(vec, speed);
	vec = vec * invert_;
	translate(vec);
}

void ar::Camera::translate(const Vec3f& vec_)
{
	transform.translate(vec_, transform.angle);
}

void ar::Camera::inputVector(Vec3f& vec_, float velocity_)
{
	inputFrontVector(vec_, velocity_);
	inputBackVector(vec_, velocity_);
	inputRightVector(vec_, velocity_);
	inputLeftVector(vec_, velocity_);
}

void ar::Camera::inputFrontVector(Vec3f& vec_, float velocity_)
{
	if (env.isPress(KeyEvent::KEY_w))
		vec_.z += velocity_;
}

void ar::Camera::inputBackVector(Vec3f& vec_, float velocity_)
{
	if (env.isPress(KeyEvent::KEY_s))
		vec_.z -= velocity_;
}

void ar::Camera::inputRightVector(Vec3f& vec_, float velocity_)
{
	if (env.isPress(KeyEvent::KEY_d))
		vec_.x -= velocity_;
}

void ar::Camera::inputLeftVector(Vec3f& vec_, float velocity_)
{
	if (env.isPress(KeyEvent::KEY_a))
		vec_.x += velocity_;
}

float ar::Camera::verticalValue(float rotatespeed_)
{
	return rotatespeed_ * env.getAxis("Vertical_UD", 0.15f);
}

float ar::Camera::horizontalValue(float rotatespeed_)
{
	return rotatespeed_ * env.getAxis("Horizontal_LR", 0.15f);
}

void ar::Camera::rotateUpdate()
{
	pointOfView(1.0f);
	angleRotate();
}


void ar::Camera::pointOfView(float interval_)
{
	lookpoint = transform.rotateMatrix(transform.angle + angle_distance, interval_);
	lookpoint += transform.position;
}

void ar::Camera::angleRotate()
{
	verticalAngleRotate(rotate_speed);
	horizontalAngleRotate(rotate_speed);

	horizontalRotateLimit(horizontal_up_limit, horizontal_low_limit);
}

void ar::Camera::verticalAngleRotate(float rotatespeed_)
{
	transform.angle.y += horizontalValue(rotatespeed_);
	transform.angle.y = std::fmod(transform.angle.y, 2 * (float)M_PI);
}

void ar::Camera::horizontalAngleRotate(float rotatespeed_)
{
	transform.angle.x += verticalValue(rotatespeed_);
}


void ar::Camera::horizontalRotateLimit(float up_limit_, float low_limit_)
{
	transform.angle.x = std::min(low_limit_, std::max(up_limit_, transform.angle.x));
}

void ar::Camera::shakeCameraCall()
{
	is_shake = true;
}

void ar::Camera::shakeCameraUpdate()
{
	if (is_shake)
	{
		std::random_device rand;
		std::mt19937 mt(rand());
		std::uniform_real_distribution<float> shake_rand(-0.1f, 0.1f);
		Vec3f shake_pos = Vec3f(shake_rand(mt), shake_rand(mt), shake_rand(mt));

		camera.setCenterOfInterestPoint(shake_pos + shake_buf);
		shake_count++;
		if (shake_count >= 30)
		{
			is_shake = false;
			shake_count = 0;
		}
	}
	CameraInfoGet.shakeCamera = [&] {shakeCameraCall(); };
}

