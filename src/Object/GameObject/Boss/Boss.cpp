#include "Boss.h"
#include "../../GameObject/CharaBase/CharaBase.h"
#include "../../GameObject/CharaBase/Enemy/EnemyHolder/EnemyHolder.h"
#include "../../GameObject/SignPost/SignPostManager.h"
#include "../../../Share/Easing/Easing.h"
#include "../../../Share/Interface/Interface.h"

#include "../../Component/Components/Material.h"
#include "../../Component/Components/Texture.h"
#include "../../../TaskManager/ObjDataManager.h"

void Boss::setup()
{
	is_active = false;
	pushcount = 0;
	HP_max = 5;
	HP = HP_max;
	is_hit = false;

	difference = 22.f;
	maxspeed = 1.35f;
	minspeed = 1.0f;
	Params->addParam("Boss difference", &difference).group("BOSS");
	Params->addParam("Boss maxspeed", &maxspeed).step(0.1f).group("BOSS");
	Params->addParam("Boss minspeed", &minspeed).step(0.1f).group("BOSS");
	Params->addParam("Boss HP", &HP).group("BOSS");
	//Params->addParam("Boss minspeed", &minspeed).step(0.1f).group("BOSS");

	collision_circle_rad = 2;

	smokeSetup();

	//addComponent<ar::Material>(ar::Material(
	//	ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
	//					 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
	//					 ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
	//					 80.0f,                               // Shininess
	//					 ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f))));	  // Emission

	bosstex = TextureGet.find("Boss");


	alpha = 1.0f;

	weakpoints = std::vector<WeakPoint>(5);

	weakpoints[0].pos = ci::Vec3f(3, 3, 0);
	weakpoints[1].pos = ci::Vec3f(3, -3, 0);
	weakpoints[2].pos = ci::Vec3f(-3, 3, 0);
	weakpoints[3].pos = ci::Vec3f(-3, -3, 0);
	weakpoints[4].pos = ci::Vec3f(0, 0, 0);
	weakpoints[0].arrow_pos = ci::Vec3f(-1, -1, -5);
	weakpoints[1].arrow_pos = ci::Vec3f(-1, 1, -5);
	weakpoints[2].arrow_pos = ci::Vec3f(1, -1, -5);
	weakpoints[3].arrow_pos = ci::Vec3f(1, 1, -5);
	weakpoints[4].arrow_pos = ci::Vec3f(0, 0, -5);


	int mesh_count = 0;
	for (int i = 0; i < weakpoints.size(); i++)
	{
		weakpoints[i].is_hit = false;
		weakpoints[i].is_obscure = false;
		weakpoints[i].can_attack = true;
		weakpoints[i].mesh1 = &ObjDataGet.find("Boss" + std::to_string(mesh_count));
		mesh_count++;
		if (mesh_count < 8)
			weakpoints[i].mesh2 = &ObjDataGet.find("Boss" + std::to_string(mesh_count));
		mesh_count++;

		weakpoints[i].tex = TextureGet.find("TargetArrow");
		weakpoints[i].mt = ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
											ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
											ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
											80.0f,                               // Shininess
											ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));
	}
	weakpoints[weakpoints.size() - 1].can_attack = false;

	arrow_scale = ci::Vec3f(2, 2, 0);
	arrow_pos = ci::Vec3f::zero();
	Params->addParam("Arrow Scale", &arrow_scale).group("BOSS").step(0.1f);
	Params->addParam("Arrow Pos", &arrow_pos).group("BOSS");


	hit_count = 0;
	is_hit_staging = false;
}

void Boss::update()
{
	if (!is_active) {
		entry();
		return;
	}
	damage();
	pushcount++;
	pushcount %= 60;
	matrix = signpostmanager->getMatrix(transform.position);

	smokeUpdate();
	hitStaging();
	keepDifference();
}

void Boss::draw()
{

}

void Boss::transDraw()
{
	if (!is_active)return;
	ci::gl::popModelView();
	ci::gl::pushModelView();
	ci::gl::enableAlphaBlending();
	drawBegin();
	ci::gl::multModelView(matrix);
	ci::gl::rotate(ci::Vec3f(0, 0, 180));

	{
		for (int i = 0; i < weakpoints.size(); i++)
		{

			if (weakpoints[i].is_obscure == false)
			{
				ci::gl::pushModelView();
				weakpoints[i].mt.apply();
				//ci::gl::drawSphere(weakpoints[i].pos, collision_circle_rad);

				ci::gl::scale(ci::Vec3f(0.035f, 0.035f, 0.035f));

				bosstex->enableAndBind();

				ci::gl::draw(*weakpoints[i].mesh1);
				if (i < weakpoints.size() - 1)
					ci::gl::draw(*weakpoints[i].mesh2);

				bosstex->disable();

				ci::gl::popModelView();
				if (weakpoints[i].can_attack)
				{
					ci::gl::pushModelView();
					weakpoints[i].tex->enableAndBind();

					ci::gl::scale(arrow_scale);

					ci::gl::drawCube(weakpoints[i].pos +
									 ci::Vec3f(0, -1.5 + sin(arrow_count) * sin(arrow_count), -4) +
									 weakpoints[i].arrow_pos + arrow_pos,
									 ci::Vec3f(1, 1, 0));

					arrow_count += 0.02;
					weakpoints[i].tex->disable();
					ci::gl::popModelView();
				}
			}

		}
	}

	drawEnd();
	ci::gl::disableAlphaBlending();

	ci::gl::popModelView();
	ci::gl::pushModelView();


	ci::gl::pushModelView();
	for (auto& it : smokes)
	{
		it->transDraw();
	}
	ci::gl::popModelView();
}

void Boss::setPlayer(std::shared_ptr<CharaBase> _player)
{
	player = _player.get();
}

void Boss::setEnemyHolder(std::shared_ptr<EnemyHolder> _eh)
{
	enemyholder = _eh.get();
}

void Boss::setSignPostManager(std::shared_ptr<ar::SignPostManager> _spm)
{
	signpostmanager = _spm.get();
}

void Boss::entry()
{
	if (is_active)return;
	if (!enemyholder->remainingEnemy() == 0) return;

	transform.position.z = player->transform.position.z + 100;

	is_active = true;
}


bool Boss::getIsExist() {
	return is_active;
}

bool Boss::isPushBullet()
{
	if (!is_active)return false;
	return pushcount == 0;

}

ci::Vec3f Boss::getWorldpos()
{
	return  matrix * ci::Vec3f::zero();
}

ci::Matrix44f Boss::getMatrcx()
{
	return matrix;
}

void Boss::damage()
{
	if (player->isCharaDashing())
	{
		int erase_obj_count = 0;
		for (int i = 0; i < weakpoints.size(); i++)
		{
			if (erase_obj_count >= weakpoints.size() - 1)
				weakpoints[i].can_attack = true;
			if (weakpoints[i].is_hit == false &&
				weakpoints[i].can_attack)
			{
				if (player->transform.position.distanceSquared(
					transform.position - weakpoints[i].pos) <
					(player->getCollisionCirclerad() + collision_circle_rad)
					*(player->getCollisionCirclerad() + collision_circle_rad)
					)
				{
					if (is_hit) return;
					HP--;
					{
						is_hit = true;
						hit_count = 0;
						is_hit_staging = true;
						weakpoints[i].is_hit = true;
					}
					return;
				}
			}
			else
			{
				erase_obj_count++;
			}
		}
	}
	is_hit = false;
}

void Boss::keepDifference()
{
	if (player->transform.position.z > transform.position.z)
	{
		maxspeed = 2;
	}

	float _difference = -player->transform.position.z + transform.position.z;

	if (_difference > difference) {
		transform.position.z += minspeed;
	}
	if (_difference < difference) {
		transform.position.z += maxspeed;
	}


}

void Boss::smokeSetup()
{
	current_damage_type = DamageType::NO_DAMAGE;
	damage_type.insert(current_damage_type);
}

void Boss::smokeUpdate()
{
	for (auto& it : smokes)
	{
		it->setCameraPos(camera_pos);
	}
	if (HP <= float(HP_max) * (2.0f / 3.0f))
		current_damage_type = DamageType::ONE_STEP;
	if (HP <= float(HP_max) * (1.0f / 3.0f))
		current_damage_type = DamageType::TWO_STEP;
	if (HP <= 0)
		current_damage_type = DamageType::THREE_STEP;

	if (damage_type.find(current_damage_type) == damage_type.end())
	{
		damage_type.clear();
		damage_type.insert(current_damage_type);

		smokePop();
		smokePop();
		//smokePop();
		//smokePop();

	}
	if (is_hit_staging == false)
	{
		if (current_damage_type == DamageType::TWO_STEP)
		{
			for (int i = 0; i < weakpoints.size(); i++)
				weakpoints[i].mt = ci::gl::Material(ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Ambient
													ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Diffuse
													ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Specular
													80.0f,                               // Shininess
													ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));
		}
		if (current_damage_type == DamageType::THREE_STEP)
		{
			for (int i = 0; i < weakpoints.size(); i++)
				weakpoints[i].mt = ci::gl::Material(ci::ColorA(1.0f, 0.0f, 0.0f, alpha),      // Ambient
													ci::ColorA(1.0f, 0.0f, 0.0f, alpha),      // Diffuse
													ci::ColorA(1.0f, 0.0f, 0.0f, alpha),      // Specular
													80.0f,                               // Shininess
													ci::ColorA(0.5f, 0.5f, 0.5f, alpha));

			alpha -= 0.008;
			if (alpha <= 0)
				smokes.clear();
		}
	}


	for (auto& it : smokes)
	{
		it->setBossWorldPos(getWorldpos());
		it->update();
	}

}

void Boss::smokePop()
{
	std::random_device rand;
	std::mt19937 mt(rand());
	std::uniform_real_distribution<float> pop_rand(-2.5f, 2.5f);

	ci::Vec3f pop_pos = ci::Vec3f(pop_rand(mt), pop_rand(mt), pop_rand(mt));

	smokes.push_back(std::make_shared<Smokes>(Smokes(pop_pos)));
}

void Boss::hitStaging()
{
	if (is_hit_staging)
	{
		if (hit_count % 10 == 0)
		{
			staging_change = !staging_change;
		}
		for (int i = 0; i < weakpoints.size(); i++)
		{
			if (weakpoints[i].is_hit)
				if (staging_change)
				{
					weakpoints[i].mt = ci::gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
														ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
														ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
														80.0f,                               // Shininess
														ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));

				}
				else
				{
					weakpoints[i].mt = ci::gl::Material(ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Ambient
														ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Diffuse
														ci::ColorA(1.0f, 0.0f, 0.0f, 1.0f),      // Specular
														80.0f,                               // Shininess
														ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f));

				}
		}

		maxspeed = 1.7f;

		std::random_device rand;
		std::mt19937 mt(rand());
		std::uniform_real_distribution<float> shake_rand(-0.4f, 0.4f);
		ci::Vec3f shake_pos = ci::Vec3f(shake_rand(mt), shake_rand(mt), 0);

		transform.position.x = shake_pos.x;
		transform.position.y = shake_pos.y;

		if (hit_count >= 60)
		{
			for (int i = 0; i < weakpoints.size(); i++)
				if (weakpoints[i].is_hit)
					weakpoints[i].is_obscure = true;
			is_hit_staging = false;
		}
	}
	else
	{
		transform.position.x = 0;
		transform.position.y = 0;
		maxspeed = 1.35f;
	}
	hit_count++;
}
