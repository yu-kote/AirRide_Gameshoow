#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::restart()
{
	transform.position = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.angle = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.scale = ci::Vec3f(0.07f, 0.07f, 0.07f);

	status = CharaStatus::NORMAL;
	speed = 1.0f;

	move_count = 0.0f;
	start_move_pos = ci::Vec2f::zero();
	end_move_pos = ci::Vec2f::zero();

	roll_count = 1.0f;
	start_roll_angle = 0.0f;
	end_roll_angle = 0.0f;

	dash_count = 0.0f;

	clash_count = 1.0f;
	clash_speed = 3.0f;

	interval_count = 1.0f;

	is_stop = false;

	move_direction = ci::Vec2f::zero();

	pos_to_ratio = ci::Vec2f::zero();
	before_pos_to_ratio = ci::Vec2f::zero();
	before_hand_normal = ci::Vec3f::zero();
	before_hand_pos = ci::Vec3f::zero();

	max_clash_count = 1.0f;
	clash_speed = 0.5f;

	hand_exist_count = 0.0f;
	start_delay = 1.7f;
}

void Player::setup()
{
	init();

	addComponent<ar::Texture>(ar::Texture("Player"));
	addComponent<ar::Material>(ar::Material(
		ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
			ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
			ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
			80.0f,                               // Shininess
			ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f))));	  // Emission

	transform.scale = ci::Vec3f(0.07f, 0.07f, 0.07f);

	operation_type = OperationType::KEY;

	move_direction = ci::Vec2f::zero();

	window_size_camera_to_player = ci::Vec2f(40.0f, 40.0f);
	pos_to_ratio = ci::Vec2f::zero();
	interval_frame = 6;
	before_pos_to_ratio = ci::Vec2f::zero();
	before_hand_normal = ci::Vec3f::zero();
	before_hand_pos = ci::Vec3f::zero();


	min_hand_normal_z_range = -0.5;
	max_hand_normal_z_range = 0.5f;
	min_hand_normal_xy_range = (float)M_PI / -3.0f;
	max_hand_normal_xy_range = (float)M_PI / 3.0f;
	min_dot_product_range = 1.0f;
	max_dot_product_range = 0.3f;
	dash_range = 30.0f;

	max_clash_count = 1.0f;
	clash_speed = 0.5f;
	start_clash_speed = 0.5f;
	end_clash_speed = 0.5f;

	hand_exist_count = 0.0f;

	interval_takes_time = 1.0f;

	start_delay = 1.7f;
}

void Player::update()
{
	changeOperationType();

	if (operation_type == OperationType::LEAPMOTION)
		operationLeap();
	else if (operation_type == OperationType::KEY)
		operationKey();

	move();
	
	// camera����͂ݏo�Ȃ��悤�ɂ���
	debugCourseOutStop();

	// stage�s��ɕϊ�
	updateStageMatrix();
}

void Player::draw()
{
	ci::gl::popMatrices();

	ci::gl::pushMatrices();
	ci::gl::multModelView(matrix);
	ci::Matrix44f mtranslate = ci::Matrix44f::createTranslation(ci::Vec3f(0.0f, 1.0f, 0.0f));
	ci::gl::multModelView(mtranslate);
	ci::Matrix44f mrotate = ci::Matrix44f::createRotation(transform.angle);
	ci::gl::multModelView(mrotate);
	mtranslate = ci::Matrix44f::createTranslation(ci::Vec3f(0.0f, -1.0f, 0.0f));
	ci::gl::multModelView(mtranslate);
	ci::Matrix44f mscale = ci::Matrix44f::createScale(transform.scale);
	ci::gl::multModelView(mscale);
	ci::Matrix44f mtranslate2 = ci::Matrix44f::createTranslation(ci::Vec3f(0.0f, 0.0f, -1.0f));
	ci::gl::multModelView(mtranslate2);

	ci::gl::draw(ObjDataGet.find("Player"));

	ci::gl::popMatrices();
	ci::gl::pushMatrices();
}

void Player::dash()
{
	if (status != CharaStatus::DASH)
		return;

	dash_count += TIME.getDeltaTime();
	if (dash_count >= 1.0f)
	{
		dash_count = 1.0f;
		status = CharaStatus::NORMAL;
	}

	speed = QuadOut(dash_count, start_speed, end_speed);
}

void Player::changeOperationType()
{
	if (LEAPHANDS.IsHandExist() && operation_type == OperationType::KEY)
	{
		operation_type = OperationType::LEAPMOTION;
		return;
	}

	if (!LEAPHANDS.IsHandExist())
	{
		operation_type = OperationType::KEY;
		return;
	}
}

void Player::operationKey()
{
	if (is_stop == true)
		return;

	start_delay = std::max(0.0f, start_delay - TIME.getDeltaTime());
	if (start_delay > 0.0f)
		return;

	debugMove();

	if (env.isPush(ci::app::KeyEvent::KEY_SPACE))
		debugRoll();

	if (env.isPush(ci::app::KeyEvent::KEY_b))
		debugDash();
}

void Player::debugMove()
{
	if (status != CharaStatus::NORMAL)
		return;

	ci::Vec2f _direction = ci::Vec2f::zero();
	if (env.isPress(ci::app::KeyEvent::KEY_j)) {
		_direction.x = 1;
	}
	if (env.isPress(ci::app::KeyEvent::KEY_l)) {
		_direction.x = -1;
	}
	if (env.isPress(ci::app::KeyEvent::KEY_i)) {
		_direction.y = 1;
	}
	if (env.isPress(ci::app::KeyEvent::KEY_k)) {
		_direction.y = -1;
	}

	if (_direction.lengthSquared() > 0) {
		_direction.normalize();
		start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
		end_move_pos = ci::Vec2f(transform.position.x, transform.position.y) + _direction * 2.0f;
		move_count = 0.0f;

		move_direction = _direction / 10.0f;
	}


}

void Player::debugRoll()
{
	if (status != CharaStatus::NORMAL)
		return;

	if (move_direction.lengthSquared() <= 0)
		return;

	isRolling(move_direction * 50.0f);
}

void Player::debugDash()
{
	if (status != CharaStatus::NORMAL)
		return;

	isAttacking();
}

void Player::operationLeap()
{
	// leapmotion�̍X�V����
	UpdateLeapHands();

	if (is_stop == true)
		return;

	// �s����̍X�V
	moveDestination();

	start_delay = std::max(0.0f, start_delay - TIME.getDeltaTime());
	if (start_delay > 0.0f)
		return;

	if (hand_exist_count < 1.0f)
		return;

	// Roll�̊m�F����
	//handNormalRotation();

	// Dash�̊m�F����
	handPosZDistance();
}

void Player::UpdateLeapHands()
{
	if (LEAPHANDS.IsHandExist())
		hand_exist_count = std::min(3.0f, hand_exist_count + TIME.getDeltaTime());
	else
		hand_exist_count = 0.0f;

	pos_to_ratio = LEAPHANDS.GetHandCenterPosToRatio();

	if (TIME.isIntervalTime(interval_frame))
	{
		before_hand_normal = LEAPHANDS.GetHandNormal();
		before_hand_pos = LEAPHANDS.GetHandCenterPos();
		before_pos_to_ratio = LEAPHANDS.GetHandCenterPosToRatio();
	}
}

void Player::moveDestination()
{
	/* destination : �ړ��� */
	ci::Vec2f destination_pos =
		ci::Vec2f(window_size_camera_to_player.x * pos_to_ratio.x,
			window_size_camera_to_player.y * pos_to_ratio.y);

	// �O�̃t���[���̃v���C���[�̍s����ƍ����݂̍s������ׂĈ�����ꍇ�A�X�V����
	if (end_move_pos == destination_pos)
		return;

	moving(destination_pos);
}

void Player::handNormalRotation()
{
	// LeapMotion �� hand ��F�����Ă��Ȃ��Ƃ��͂���
	if (!LEAPHANDS.IsHandExist())
		return;

	// ���̖@�����^������z������ [�|�S�T�x��菬����]�A[�S�T�x���傫���ꍇ] �͂���
	if (LEAPHANDS.GetHandNormal().z > max_hand_normal_z_range ||
		LEAPHANDS.GetHandNormal().z < min_hand_normal_z_range)
		return;

	float start_theta = std::atan2(before_hand_normal.x - 0.0f, before_hand_normal.y - (-1.0f));

	// 8frame�O�̖@����-60~60�ȓ��ɂȂ��Ȃ�͂���
	if (start_theta < min_hand_normal_xy_range &&
		start_theta > max_hand_normal_xy_range)
		return;

	// 6frame�O�̖@���ƍ����݂̖@���Ƃ̓���
	float dot_product = std::abs((before_hand_normal.x * LEAPHANDS.GetHandNormal().x) + (before_hand_normal.y * LEAPHANDS.GetHandNormal().y));

	// 6frame�O�̎�̖@���ƍ��̖@���Ƃ̓��ς� [�O�ȏ�`�T�S�x����] �̏ꍇ�͂���
	if (dot_product <= min_dot_product_range && dot_product > max_dot_product_range)
		return;

	// 6frame�O�̖@���ƍ��̖@���Ƃ̊p�x
	float theta = std::atan2(LEAPHANDS.GetHandNormal().x - before_hand_normal.x, LEAPHANDS.GetHandNormal().y - before_hand_normal.y);

	// |a| * |b|
	/*float vec_a_to_b = std::sqrtf((before_hand_normal.x * before_hand_normal.x) + (before_hand_normal.y * before_hand_normal.y)) *
		std::sqrtf((LEAPHANDS.GetHandNormal().x * LEAPHANDS.GetHandNormal().x) + (LEAPHANDS.GetHandNormal().y * LEAPHANDS.GetHandNormal().y));*/

	// �O�ό��� |a| * |b| * sin��
	//float cross_product = vec_a_to_b * std::sin(theta);

	// ���[���������
	ci::Vec2f distance_vec_normal = pos_to_ratio - before_pos_to_ratio;

	// �Ƃ�܃m�[�}���C�Y
	(distance_vec_normal).normalize();

	isRolling(distance_vec_normal * 4.0f);
}

void Player::handPosZDistance()
{
	float distance_z = LEAPHANDS.GetHandCenterPos().z - before_hand_pos.z;

	// ���z���ɑ΂��Ă̈ړ��ʂ������Ȃ������ꍇ�͂���
	if (distance_z < dash_range)
		return;

	ci::Vec3f hand_distance = before_hand_pos - LEAPHANDS.GetHandCenterPos();
	float distance = std::sqrtf((hand_distance.x * hand_distance.x) +
		(hand_distance.y * hand_distance.y) +
		(hand_distance.z * hand_distance.z));

	if (distance < dash_range * 2.0f)
		return;

	if (!isAttacking())
		return;

	ci::Vec2f dash_move = before_hand_pos.xy() - LEAPHANDS.GetHandCenterPos().xy();
	(dash_move).normalize();

	moving(transform.position.xy() + dash_move * 10000.0f);
}
