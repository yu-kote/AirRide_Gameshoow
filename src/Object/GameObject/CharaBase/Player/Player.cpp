#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::setup()
{
	LEAPHANDS.Setup();

	operation_type = OperationType::KEY;

	transform.position = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.angle = ci::Vec3f(0.0f, 0.0f, 0.0f);
	transform.scale = ci::Vec3f(0.0f, 0.0f, 1.0f);

	addComponent<ar::Color>();

	status = CharaStatus::NORMAL;
	speed = 0.0f;

	move_count = 0.0f;
	start_move_pos = ci::Vec2f::zero();
	end_move_pos = ci::Vec2f::zero();

	roll_angle = 0.0f;
	roll_count = 0.0f;
	start_roll_angle = 0.0f;
	end_roll_angle = 0.0f;

	move_direction = ci::Vec2f::zero();

	dash_count = 0.0f;
	start_dash_pos = 0.0f;
	end_dash_pos = 0.0f;

	window_size_camera_to_player = ci::Vec2f(40.0f, 40.0f);
	pos_to_ratio = ci::Vec2f::zero();
	interval_frame = 6;
	before_pos_to_ratio = ci::Vec2f::zero();
	before_hand_normal = ci::Vec3f::zero();
	before_hand_pos = ci::Vec3f::zero();


	window_size = ci::Vec3f(10.0f * 100.0f / 171.0f * 2.0f,
		10.0f * 100.0f / 171.0f * 2.0f,
		0.0f);


	min_hand_normal_z_range = -0.5;
	max_hand_normal_z_range = 0.5f;
	min_hand_normal_xy_range = (float)-M_PI / 3.0f;
	max_hand_normal_xy_range = (float)M_PI / 3.0f;
	min_dot_product_range = 1.0f;
	max_dot_product_range = 0.5f;
	dash_range = 50.0f;
}

void Player::update()
{
	if (operation_type == OperationType::LEAPMOTION)
		operationLeap();
	else if (operation_type == OperationType::KEY)
		operationKey();
	

	move();

	// cameraからはみ出ないようにする
	//collisionToWindow();
	debugCourseOutStop();

	// stage行列に変換
	updateStageMatrix();
}

void Player::draw()
{
	ci::gl::popMatrices();

	ci::gl::pushMatrices();
	ci::gl::multModelView(matrix);
	ci::Matrix44f mrotate = ci::Matrix44f::createRotation(ci::Vec3f(0.0f, 0.0f, roll_angle));
	ci::gl::multModelView(mrotate);

	ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());

	ci::gl::popMatrices();
	ci::gl::pushMatrices();
}

void Player::operationKey()
{
	debugMove();
	debugRoll();
	debugDash();
}

void Player::debugMove()
{
	if (status != CharaStatus::NORMAL)
		return;

	ci::Vec2f _direction = ci::Vec2f::zero();
	if (env.isPress(ci::app::KeyEvent::KEY_j)) {
		_direction.x = 3;
	}
	if (env.isPress(ci::app::KeyEvent::KEY_l)) {
		_direction.x = -3;
	}
	if (env.isPress(ci::app::KeyEvent::KEY_i)) {
		_direction.y = 3;
	}
	if (env.isPress(ci::app::KeyEvent::KEY_k)) {
		_direction.y = -3;
	}
	if (env.isPush(ci::app::KeyEvent::KEY_z)) {
		goToRolling(transform.position.xy() + _direction.safeNormalized()*4);
	}

	if (_direction.lengthSquared() > 0) {
		_direction.normalize();
		_direction *= 0.1f;
		start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
		end_move_pos += _direction;
		move_count = 0.0f;

		move_direction = _direction;
	}


}

void Player::debugRoll()
{
	if (status != CharaStatus::NORMAL)
		return;

	if (!env.isPush(ci::app::KeyEvent::KEY_SPACE))
		return;

	if (move_direction.lengthSquared() <= 0)
		return;

	if (move_direction.x > 0)
		rolling(move_direction * 50.0f, RollDirection::RIGHT);
	else
		rolling(move_direction * 50.0f, RollDirection::LEFT);
}

void Player::debugDash()
{
	if (status != CharaStatus::NORMAL)
		return;

	if (!env.isPush(ci::app::KeyEvent::KEY_b))
		return;

	attack();
}

void Player::operationLeap()
{
	// leapmotionの更新処理
	UpdateLeapHands();

	// 行き先の更新
	moveDestination();

	// Rollの確認処理
	handNormalRotation();

	// Dashの確認処理
	handPosZDistance();
}

void Player::moveDestination()
{
	// ロール、ダッシュ状態では普通の横移動はしないではじく
	if (status != CharaStatus::NORMAL)
		return;
	/* destination : 移動先 */
	ci::Vec2f destination_pos =
		ci::Vec2f(window_size_camera_to_player.x * pos_to_ratio.x,
			window_size_camera_to_player.y * pos_to_ratio.y);

	// 前のフレームのプレイヤーの行き先と今現在の行き先を比べて違った場合、更新する
	if (end_move_pos == destination_pos)
		return;

	start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
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

	// LeapMotion が hand を認識していないときはじく
	if (!LEAPHANDS.IsHandExist())
		return;

	// 掌の法線が真下からz方向に [－４５度より小さい]、[４５度より大きい場合] はじく
	if (LEAPHANDS.GetHandNormal().z > max_hand_normal_z_range ||
		LEAPHANDS.GetHandNormal().z < min_hand_normal_z_range)
		return;

	float start_theta = std::atan2(LEAPHANDS.GetHandNormal().x - 0.0f, LEAPHANDS.GetHandNormal().y - (-1.0f));

	if (start_theta < min_hand_normal_xy_range &&
		start_theta > max_hand_normal_xy_range)
		return;

	// 6frame前の法線と今現在の法線との内積
	float dot_product = (before_hand_normal.x * LEAPHANDS.GetHandNormal().x) + (before_hand_normal.y * LEAPHANDS.GetHandNormal().y);

	// 6frame前の手の法線と今の法線との内積が [０以上～９０度未満] の場合はじく
	if (dot_product <= min_dot_product_range && dot_product > max_dot_product_range)
		return;

	// 6frame前の法線と今の法線との角度
	float theta = std::atan2(LEAPHANDS.GetHandNormal().x - before_hand_normal.x, LEAPHANDS.GetHandNormal().y - before_hand_normal.y);

	// |a| * |b|
	float vec_a_to_b = std::sqrtf((before_hand_normal.x * before_hand_normal.x) + (before_hand_normal.y * before_hand_normal.y)) *
		std::sqrtf((LEAPHANDS.GetHandNormal().x * LEAPHANDS.GetHandNormal().x) + (LEAPHANDS.GetHandNormal().y * LEAPHANDS.GetHandNormal().y));

	// 外積公式 |a| * |b| * sinθ
	float cross_product = vec_a_to_b * std::sin(theta);

	// ロールする方向
	ci::Vec2f distance_vec_normal = pos_to_ratio - before_pos_to_ratio;

	// とりまノーマライズ
	(distance_vec_normal).normalize();

	// 今現在の位置と移動先の位置のノーマライズしたベクトルと真下のベクトルとの角度
	float direction_theta = std::atan2(distance_vec_normal.x - 0.0f, distance_vec_normal.y - (-1.0f));

	// 手が反時計回りしたとき
	if (cross_product < 0.0f)
	{
		// 移動先が右方向の場合はじく
		if (direction_theta > 0.0f)
			return;

		end_roll_angle = max_roll_angle;
	}
	// 手が時計回りしたとき
	else if (cross_product >= 0.0f)
	{
		// 移動先が左方向の場合はじく
		if (direction_theta <= 0.0f)
			return;

		end_roll_angle = -max_roll_angle;
	}


	////////////////////////////////////////////////////////////////////////////////////
	// ロール中の移動処理がかけていない
	////////////////////////////////////////////////////////////////////////////////////
	start_move_pos = ci::Vec2f(transform.position.x, transform.position.y);
	end_move_pos = end_move_pos + distance_vec_normal * 10.0f;
	////////////////////////////////////////////////////////////////////////////////////
	roll_count = 0.0f;
	status = CharaStatus::ROLL;
}

void Player::handPosZDistance()
{
	if (status != CharaStatus::NORMAL)
		return;

	float distance_z = LEAPHANDS.GetHandCenterPos().z - before_hand_pos.z;

	ci::app::console() << LEAPHANDS.GetHandCenterPos().z << std::endl;

	// 手のz軸に対しての移動量が満たなかった場合はじく
	if (distance_z < dash_range)
		return;

	dash_count = 0.0f;
	status = CharaStatus::DASH;
}
