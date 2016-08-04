#pragma once
#include "../CharaBase.h"
#include "../../SignPost/SignPostManager.h"



class Enemy : public CharaBase
{
public:
	Enemy();
	~Enemy();
	void setup() override;
	void update() override;
	void draw() override;

	void setSignPostManager(std::shared_ptr<ar::SignPostManager>);

private:

	ci::Matrix44f matrix;
	std::shared_ptr<ar::SignPostManager> signpostmanager;
};

