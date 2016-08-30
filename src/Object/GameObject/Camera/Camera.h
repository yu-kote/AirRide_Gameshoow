#pragma once
#include "cinder/app/AppNative.h"
#include "../../GameObject/GameObject.h"
#include "../../../Object/GameObject/CharaBase/CharaBase.h"
#include "cinder/Camera.h"
#include "../../../Share/Interface/Interface.h"

namespace ar {

	class Camera : public GameObject {
	public:
		Camera();

		void setup()override;
		void update()override;

		void draw()override;

		void setMoveDistance(const ci::Vec3f& move_distance_) { move_distance = move_distance_; }
		void setAngleDistance(const ci::Vec3f& angle_distance_) { angle_distance = angle_distance_; }

		void setEyePoint(ci::Vec3f);
		void setCenterOfInterestPoint(ci::Vec3f);
		void setChara(std::shared_ptr<CharaBase>);

		//ÉJÉÅÉâÇÃà íu
		ci::Vec3f getCenterOfInterestPoint();

	private:
		ci::CameraPersp camera;
		CharaBase* chara;
		bool camera_run;


		ci::Vec3f move_distance;
		ci::Vec3f angle_distance;
		ci::Vec3f lookpoint;

		ci::Vec3f look_vec;
		ci::Vec3f root_vec;


	private:
		void cameraDecision(const ci::Vec3f& position_,
							const ci::Vec3f& lookpoint_);

	private: // à⁄ìÆ
		void moveUpdate(int invert_ = 1);

		void translate(const ci::Vec3f& vec_);

		void inputVector(ci::Vec3f& vec_, float velocity_);
		void inputFrontVector(ci::Vec3f& vec_, float velocity_);
		void inputBackVector(ci::Vec3f& vec_, float velocity_);
		void inputRightVector(ci::Vec3f& vec_, float velocity_);
		void inputLeftVector(ci::Vec3f& vec_, float velocity_);

	private:
		float verticalValue(float velocity_);
		float horizontalValue(float velocity_);

	private: // âÒì]
		void rotateUpdate();

	private: // FPSâÒì]

		void pointOfView(float interval_);
		void angleRotate();

	private:
		void verticalAngleRotate(float rotatespeed_);


		void horizontalAngleRotate(float rotatespeed_);
		void horizontalRotateLimit(float up_limit_, float low_limit_);

		float rotate_speed = (float)M_PI / 90.0f;
		float horizontal_up_limit = (float)-M_PI / 2.1f;
		float horizontal_low_limit = (float)M_PI / 2.1f;
	};
}