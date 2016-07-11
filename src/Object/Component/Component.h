#pragma once
#include "../Object.h"
#include "../Component/Components/Transform.h"

namespace ar {


	// •”•i
	class Component : public Object {
	public:
		virtual void setup() {}

		virtual void update() {}

		virtual void drawBegin() {}
		virtual void drawEnd() {}
		virtual void draw() {}

		ar::Transform transform;

	protected:

	private:

	};

}
