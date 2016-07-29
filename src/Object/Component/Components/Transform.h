#pragma once
#include "cinder/app/AppNative.h"

namespace ar {

	class Transform {
	public:

		Transform() {
			position = ci::Vec3f::zero();
			angle = ci::Vec3f::zero();
			rotation = ci::Quatf::identity();
			scale = ci::Vec3f(1.0f, 1.0f, 1.0f);
		}

	public:
		// �X�V����ꏊ

		// ����
		void lookAt(const Transform& target_);
		void lookAt(const ci::Vec2f& position_);

		// �I�C���[�p�ŃN�H�[�^�j�I������]
		void rotate(const ci::Vec3f& angle_);
		void rotate(ci::Vec3f axis_, float angle_);
		void rotate(float angle_x_, float angle_y_, float angle_z_);


		// �ړ�
		void translate(const ci::Vec3f& translation_);
		ci::Vec3f translate(const ci::Vec3f& vector_, const ci::Vec3f& angle_);
		void translate(float x_, float y_, float z_);


		ci::Vec3f rotateMatrix(const ci::Vec3f& angle_, float z_);

	public:

		void console() {
			ci::app::console() << "Position : " << position << std::endl;
			ci::app::console() << "Rotation : " << rotation << std::endl;
		}

	public:
		ci::Vec3f position;
		ci::Vec3f angle;
		ci::Quatf rotation;
		ci::Matrix44f local_matrix;
		ci::Vec3f scale;

		ci::Vec3f direction;

	};

}