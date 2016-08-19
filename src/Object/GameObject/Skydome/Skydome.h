#pragma once 
#include "../../GameObject/GameObject.h"
#include "../../Component/Components/Texture.h"


class Skydome : public ar::GameObject
{
public:
	void setup() override;
	void update() override;
	void draw() override;

	void setTerget(std::shared_ptr<ar::GameObject>);


private:
	ar::GameObject* terget;



	ci::Vec3f pos;
};
