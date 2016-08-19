#pragma once
#include "../../GameObject/GameObject.h"
#include "cinder/gl/Texture.h"  
#include "cinder/imageIo.h"

class Skydome : public ar::GameObject
{
public:
	void setup() override;
	void update() override;
	void draw() override;

	void setTerget(std::shared_ptr<ar::GameObject>);

private:
	ar::GameObject* terget;

	ci::gl::TextureRef tex;
	ci::Vec3f pos;
};


