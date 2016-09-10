#pragma once
#include "../../GameObject.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Material.h"
#include "../../Obstacle/Particle/Particle.h"


class Boss;
class CharaBase;

class Bullet : public ar::GameObject
{
public:
	Bullet(ci::Vec3f);

	void update() override;

	void draw()override;

	bool isErase();

	void bomb();
	void setCameraPos(ci::Vec3f);

private:

	int bomb_count;
	int count;
	ci::TriMesh* mesh;
	ci::gl::TextureRef tex;
	ci::gl::Material mt;

	std::list<std::shared_ptr<ar::ParticleController>> particle;


	bool is_bomb;
};



class Bullets : public ar::GameObject
{
public:
	void setup() override;
	void update()override;
	void draw()override;

	void setBoss(std::shared_ptr<Boss>);
	void setPlayer(std::shared_ptr<CharaBase>);
	void setCameraPos(ci::Vec3f);

private:
	std::list<Bullet> bullets;
	Boss* boss;
	CharaBase* player;


};

