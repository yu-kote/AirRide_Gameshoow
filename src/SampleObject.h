#pragma once
#include "Object/GameObject/GameObject.h"
#include "Object/Component/Components/Color.h"
#include "Input/InputEvent.h"

// サンプル（コンポーネントの使いかたの例）
class SampleObject : public GameObject {
public:

	SampleObject() {
		setup();
	}

	void setup()override {
		transform.position = ci::Vec3f(0.0f, 0.0f, 10.0f);

		addComponent<Color>(ci::ColorA(1.0f, 1.0f, 1.0f));
		c_color = getComponent<Color>();
	}

	void update()override {
		if (env.isPush(ci::app::KeyEvent::KEY_1))
		{
			c_color->setColor(ci::ColorA(1.0f, 0.0f, 0.0f));
		}
		else if (env.isPush(ci::app::KeyEvent::KEY_2))
		{
			c_color->setColor(ci::ColorA(0.0f, 1.0f, 0.0f));
		}
	}

	void draw()override {
		ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f(1.0f, 1.0f, 1.0f));
	}

private:

	std::shared_ptr<Color> c_color;
};