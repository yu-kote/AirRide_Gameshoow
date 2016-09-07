#include "Title.h"
#include "../SceneCategory/GameMain.h"
#include "../../Input/InputEvent.h"
#include "../../Input/LeapMotion/LeapHands/LeapHands.h"

Title::Title()
{
	setup();
}

void Title::setup()
{
	
	color_r = 0.0f;
	color_g = 0.0f;
	color_b = 0.0f;
	c_Easing::apply(color_r, 1.0f, EasingFunction::ExpoIn, 60);
	c_Easing::apply(color_g, 1.0f, EasingFunction::ExpoIn, 60);
	c_Easing::apply(color_b, 1.0f, EasingFunction::ExpoIn, 60);
	update_count = 0;
	end_count = 0;
}

void Title::update()
{
	if (c_Easing::isEnd(color_b)) {
		update_count++;
		if (update_count == 1) {
			end_flag = false;
			next_count = 0;
			ui.setup();
			ui.titleSetup();
			entities.setupGameObject();
			if (SoundGet.find("TitleBGM")->isEnabled())
				SoundGet.find("TitleBGM")->stop();
			else
				SoundGet.find("TitleBGM")->start();
			SoundGet.find("TitleBGM")->setLoopEnabled(true);
		}
		ui.titleUpdate();
		entities.updateGameObject();
	}
	if (end_flag == true &&
		end_count == 1) {
		c_Easing::apply(color_r, 0.0f, EasingFunction::ExpoIn, 60);
		c_Easing::apply(color_g, 0.0f, EasingFunction::ExpoIn, 60);
		c_Easing::apply(color_b, 0.0f, EasingFunction::ExpoIn, 60);
	}

}

void Title::draw()
{
	if (!UIType::is_loop) {
		ci::gl::clear(ColorA(color_r, color_g, color_b, 1.0f));
		ui.titleDraw();
		entities.drawGameObject();
	}
	else {
		setup();
		UIType::is_loop = false;
	}
}

void Title::shift()
{
	
	if (update_count >= 1) {
		if (env.isPress(KeyEvent::KEY_RETURN) ||
			LEAPHANDS.IsHandExist())
		{
			ui.ui_data["開始ゲージ"]->Active();
			next_count += 1;
		}
		else {
			ui.ui_data["開始ゲージ"]->setEnd();
			next_count = 0;
		}
		

		ui.ui_data["開始ゲージ"]->gaugeChangeX(next_count, 60);
	}
	if (end_flag == true) {
		end_count++;
	}
	if (update_count >= 1) {
		if (ui.ui_data["開始ゲージ"]->gaugeGetIsMax()) {
			ui.ui_data["R"]->setEnd();
			ui.ui_data["I"]->setEnd();
			ui.ui_data["D"]->setEnd();
			ui.ui_data["E"]->setEnd();
			ui.ui_data["O"]->setEnd();
			ui.ui_data["N"]->setEnd();
			ui.ui_data["T"]->setEnd();
			ui.ui_data["H"]->setEnd();
			ui.ui_data["E2"]->setEnd();
			ui.ui_data["S"]->setEnd();
			ui.ui_data["K"]->setEnd();
			ui.ui_data["Y"]->setEnd();
			ui.ui_data["!"]->setEnd();
			ui.ui_data["スタート"]->setEnd();
			end_flag = true;
			if (next_count == 61 &&
				end_count == 1) {
				SoundGet.find("TitleBGM")->disable();
				SoundGet.find("Start")->start();
			}

		}
	}
	
	if (end_count >= 60) {
		c_Easing::clear(color_r);
		c_Easing::clear(color_g);
		c_Easing::clear(color_b);
		UIType::erase();
		UIObjects::erase();
		UIState::erase();
		EasingType::erase();
		Scene::createScene<GameMain>(new GameMain());
		
	}
	
}

void Title::shutdown()
{
	entities.Alldestroy();
}
