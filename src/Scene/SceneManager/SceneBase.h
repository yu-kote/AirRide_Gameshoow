#pragma once

class SceneBase {
public:

	virtual void setup() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void shift() = 0;
	virtual void shutdown() = 0;

};