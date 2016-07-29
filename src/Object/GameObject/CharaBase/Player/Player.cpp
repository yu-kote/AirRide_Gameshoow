#include "Player.h"

Player::Player()
{
	
}

Player::~Player()
{

}

void Player::setup()
{
	leap_hands.Setup();

	window_size_camera_to_player = ci::Vec2f(40.0f, 40.0f);
	pos_to_ratio = ci::Vec2f::zero();
	interval_frame = 6;
	before_pos_to_ratio = ci::Vec2f::zero();
	before_hand_normal = ci::Vec3f::zero();
	before_hand_pos = ci::Vec3f::zero();

	min_hand_normal_z_range = -0.5;
	min_hand_normal_z_range = 0.5f;
	min_hand_normal_xy_range = -M_PI / 3.0f;
	max_hand_normal_xy_range = M_PI / 3.0f;
	min_dot_product_range = 1.0f;
	max_dot_product_range = 0.5f;
	dash_range = 50.0f;
}

void Player::update()
{
	// leapmotion�̍X�V����
	UpdateLeapHands();

	// �s����̍X�V
	moveDestination();

	// Roll�̊m�F����
	handNormalRotation();

	// Dash�̊m�F����
	handPosZDistance();

	roll();
	dash();
	move();
}

void Player::draw()
{
	pushModelView();

	getComponent<ar::Color>()->drawBegin();
	ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());
	getComponent<ar::Color>()->drawEnd();
	popModelView();
}

void Player::move()
{
	move_count += TIME.getDeltaTime();
	if (move_count >= 1.0f)
		move_count = 1.0f;

	// ���ړ�
	transform.position = QuadOut(move_count, start_move_pos, end_move_pos);

	// Z���ړ�
	transform.position += speed;
}

void Player::moveDestination()
{
	// ���[���A�_�b�V����Ԃł͕��ʂ̉��ړ��͂��Ȃ��ł͂���
	if (status != CharaStatus::NORMAL)
		return;
	/* destination : �ړ��� */
	ci::Vec3f destination_pos =
		ci::Vec3f(window_size_camera_to_player.x * pos_to_ratio.x,
			window_size_camera_to_player.y * pos_to_ratio.y,
			transform.position.z);

	// �O�̃t���[���̃v���C���[�̍s����ƍ����݂̍s������ׂĈ�����ꍇ�A�X�V����
	if (end_move_pos == destination_pos)
		return;

	start_move_pos = transform.position;
	end_move_pos = destination_pos;
	move_count = 0.0f;
}

void Player::UpdateLeapHands()
{
	pos_to_ratio = LEAPHANDS.GetHandCenterPosToRatio();

	if (TIME.isIntervalTime(interval_frame))
	{
		before_hand_normal = LEAPHANDS.GetHandNormal();
		before_hand_pos = LEAPHANDS.GetHandCenterPos();
		before_pos_to_ratio = LEAPHANDS.GetHandCenterPosToRatio();
	}
}

void Player::handNormalRotation()
{
	if (status != CharaStatus::NORMAL)
		return;

	// LeapMotion �� hand ��F�����Ă��Ȃ��Ƃ��͂���
	if (!LEAPHANDS.IsHandExist())
		return;

	// ���̖@�����^������z������ [�|�S�T�x��菬����]�A[�S�T�x���傫���ꍇ] �͂���
	if (LEAPHANDS.GetHandNormal().z > max_hand_normal_z_range ||
		LEAPHANDS.GetHandNormal().z < min_hand_normal_z_range)
		return;

	float start_theta = std::atan2(LEAPHANDS.GetHandNormal().x - 0.0f, LEAPHANDS.GetHandNormal().y - (-1.0f));

	if (start_theta < min_hand_normal_xy_range ||
		start_theta > max_hand_normal_xy_range)
		return;

	// 6frame�O�̖@���ƍ����݂̖@���Ƃ̓���
	float dot_product = (before_hand_normal.x * LEAPHANDS.GetHandNormal().x) + (before_hand_normal.y * LEAPHANDS.GetHandNormal().y);

	// 6frame�O�̎�̖@���ƍ��̖@���Ƃ̓��ς� [�O�ȏ�`�X�O�x����] �̏ꍇ�͂���
	if (dot_product >= min_dot_product_range && dot_product < max_dot_product_range)
		return;

	// 6frame�O�̖@���ƍ��̖@���Ƃ̊p�x
	float theta = std::atan2(LEAPHANDS.GetHandNormal().x - before_hand_normal.x, LEAPHANDS.GetHandNormal().y - before_hand_normal.y);

	// |a| * |b|
	float vec_a_to_b = std::sqrtf((before_hand_normal.x * before_hand_normal.x) + (before_hand_normal.y * before_hand_normal.y)) *
		std::sqrtf((LEAPHANDS.GetHandNormal().x * LEAPHANDS.GetHandNormal().x) + (LEAPHANDS.GetHandNormal().y * LEAPHANDS.GetHandNormal().y));

	// �O�ό��� |a| * |b| * sin��
	float cross_product = vec_a_to_b * std::sin(theta);

	// ���[���������
	ci::Vec2f distance_vec_normal = pos_to_ratio - before_pos_to_ratio;

	// �Ƃ�܃m�[�}���C�Y
	(distance_vec_normal).normalize();

	// �����݂̈ʒu�ƈړ���̈ʒu�̃m�[�}���C�Y�����x�N�g���Ɛ^���̃x�N�g���Ƃ̊p�x
	float direction_theta = std::atan2(distance_vec_normal.x - 0.0f, distance_vec_normal.y - (-1.0f));

	// �肪�����v��肵���Ƃ�
	if (cross_product < 0.0f)
	{
		// �ړ��悪�E�����̏ꍇ�͂���
		if (direction_theta > 0.0f)
			return;
		
		end_roll_angle = max_roll_angle;
	}
	// �肪���v��肵���Ƃ�
	else if (cross_product >= 0.0f)
	{
		// �ړ��悪�������̏ꍇ�͂���
		if (direction_theta <= 0.0f)
			return;

		end_roll_angle = -max_roll_angle;
	}


	////////////////////////////////////////////////////////////////////////////////////
	// ���[�����̈ړ������������Ă��Ȃ�
	////////////////////////////////////////////////////////////////////////////////////
	start_move_pos = transform.position;
	end_move_pos = transform.position +
		ci::Vec3f(distance_vec_normal.x * 10.0f,
			distance_vec_normal.y * 10.0f,
			transform.position.z);
	////////////////////////////////////////////////////////////////////////////////////
	roll_count = 0.0f;
	status = CharaStatus::ROLL;
}

void Player::handPosZDistance()
{
	if (status != CharaStatus::NORMAL)
		return;

	float distance_z = before_hand_pos.z - LEAPHANDS.GetHandCenterPos().z;
	
	// ���z���ɑ΂��Ă̈ړ��ʂ������Ȃ������ꍇ�͂���
	if (distance_z < dash_range)
		return;

	dash_count = 0.0f;
	status = CharaStatus::DASH;
}
