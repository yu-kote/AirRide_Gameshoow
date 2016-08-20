#pragma once 
#include "../../GameObject/GameObject.h"
#include "../../Component/Components/Texture.h"
#include "../../GameObject/CharaBase/CharaBase.h"


namespace ar
{
	class Skydome : public ar::GameObject
	{
	public:
		void setup() override;
		void update() override;
		void draw() override;

		void setTerget(std::shared_ptr<CharaBase> target_);


	private:
		CharaBase* target;



		ci::Vec3f pos;
	};
}
