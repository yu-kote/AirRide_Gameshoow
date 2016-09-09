#include "Result.h"

Result::Result()
{
	setup();
}

void Result::setup()
{
	game_count = 0;
	end_count = 0;
	end = false;
	
	entities.setupGameObject();
	color = des::Vec3f(1.0f, 1.0f, 1.0f);
	if (!UIType::is_ending) {
		ui.resultSetup();
		SoundGet.find("Result")->start();
	}
	else {
		ui.endingSetup();
		color = des::Vec3f(0.0f, 0.0f, 0.0f);
	}
	
}

void Result::draw()
{
	ci::gl::clear(ColorA(color.x, color.y, color.z, 1.0f));

	ui.resultDraw();


}

void Result::update()
{
	if (!UIType::is_ending) {
		game_count++;
		ui.resultUpdate();
		entities.updateGameObject();
	}
	else {
		ending();
	}
}

void Result::shift()
{
	if (!UIType::is_ending) {
		if (game_count == 500) {
			ui.ui_data["Rank1"]->setEnd();
			ui.ui_data["Rank2"]->setEnd();
			ui.ui_data["Rank3"]->setEnd();
			ui.ui_data["Rank4"]->setEnd();
			ui.ui_data["Rank5"]->setEnd();
			ui.ui_data["ResultTime"]->setEnd();
			ui.ui_data["ƒŠƒUƒ‹ƒg"]->setEnd();
		}
		if (game_count == 600) {
			c_Easing::apply(color.x, 0.0f, EasingFunction::ExpoIn, 60);
			c_Easing::apply(color.y, 0.0f, EasingFunction::ExpoIn, 60);
			c_Easing::apply(color.z, 0.0f, EasingFunction::ExpoIn, 60);
		}
		if (game_count >= 600 &&
			c_Easing::isEnd(color.x)) {
			UIType::is_ending = true;
		}
	}
	if (end&&
		c_Easing::isEnd(color.x)) {
		UIType::erase();
		UIObjects::erase();
		UIState::erase();
		EasingType::erase();
		UIType::is_loop = true;
		UIType::is_ending = false;
		ui.ui_data.clear();
		Scene::createScene<Title>(new Title());
	}
}

void Result::shutdown()
{
	entities.Alldestroy();
}

void Result::ending()
{
	end_count++;
	if (end_count == 1) {
		ui.ui_data["‚¨”æ‚ê"]->Active();
		c_Easing::apply(color.x, 1.0f, EasingFunction::ExpoIn, 60);
		c_Easing::apply(color.y, 1.0f, EasingFunction::ExpoIn, 60);
		c_Easing::apply(color.z, 1.0f, EasingFunction::ExpoIn, 60);
	}
	if (end_count == 420) {
		c_Easing::apply(color.x, 0.0f, EasingFunction::ExpoIn, 60);
		c_Easing::apply(color.y, 0.0f, EasingFunction::ExpoIn, 60);
		c_Easing::apply(color.z, 0.0f, EasingFunction::ExpoIn, 60);
		end = true;
	}

}

