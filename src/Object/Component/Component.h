#pragma once
#include "../Object.h"
#include "../Component/Components/Transform.h"

// •”•i
class Component : public Object {
public:
	virtual void setup(){}

	virtual void update() {}

	virtual void drawBegin() {}
	virtual void drawEnd() {}
	virtual void draw() {}

	Transform transform;

protected:

private:

};

