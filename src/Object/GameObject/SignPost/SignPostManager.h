#pragma once
#include "../GameObject.h"
#include "Signpost.h"

class Player;

namespace ar {

	class SignPostManager : public GameObject {
	public:
		SignPostManager(bool is_tutorial_ = false);

		void setup();
		void update();
		void draw();


		ci::Matrix44f getMatrix(ci::Vec3f);
		ci::Vec3f getStagePos(ci::Vec3f);

		void setPlayer(std::shared_ptr<Player> player_) { player = player_; }

	private:
		std::vector<SignPost> signposts;

		void postLoad();
		void setDirection();
		void setRingQuat();
		void setLength();

		void ringDraw();
		void pointDraw();
		float round_length;
		std::vector<ar::SignPost>::iterator getNeerSignPost(ci::Vec3f);
		std::vector<ar::SignPost>::iterator prevIterator(std::vector<ar::SignPost>::iterator);

		std::shared_ptr<Player> player;


		bool is_tutorial;

	};
}