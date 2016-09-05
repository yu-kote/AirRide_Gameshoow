#include "UIPlate.h"
#include "../src/Input/LeapMotion/LeapHands/LeapHands.h"
#include "../../Share/Resize.h"
#include "../../Share/Share.h"

void UIPlate::titleSetup()
{
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		if (ui_data[(*it)]->getUIType() == UITYPE::FontUI ||
			ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
			font[(*it)] = Font(ui_data[(*it)]->fontGetPath(), ui_data[(*it)]->fontGetSize());
			continue;
		}
		TEX.set((*it), ui_data[(*it)]->getTexturePath());
		if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
			TEX.set(ui_data[(*it)]->gaugeGetTexturePath(), ui_data[(*it)]->gaugeGetTexturePath());
		}
	}
	ui_data["R"]->Active();
	ui_data["I"]->Active();
	ui_data["D"]->Active();
	ui_data["E"]->Active();
	ui_data["O"]->Active();
	ui_data["N"]->Active();
	ui_data["T"]->Active();
	ui_data["H"]->Active();
	ui_data["E2"]->Active();
	ui_data["S"]->Active();
	ui_data["K"]->Active();
	ui_data["Y"]->Active();
	ui_data["!"]->Active();
	ui_data["スタート"]->Active();

}

void UIPlate::titleUpdate()
{
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		ui_data[(*it)]->update();
	}


	ResizeGet.setPerspCameraResize = [&]()
	{
		float width = 800 + (getWindowSize().x - WIDTH);
		float height = 600 + (getWindowSize().y - HEIGHT);
		float offsetx = 170;
		float offsety = -60;

		if (getWindowSize().x == WIDTH)
			camera_o.setOrtho(0, 800,
							  600, 0,
							  1, 10);
		else
			camera_o.setOrtho(-width / 4 + offsetx,
							  width / 2 + offsetx,//getWindowCenter().x + width,
							  height + offsety,
							  0 + offsety,
							  1, 10);
	};
}

void UIPlate::titleDraw()
{
	ci::gl::disableDepthRead();
	ci::gl::enableAlphaBlending();
	ci::gl::setMatrices(camera_o);
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		if (ui_data[(*it)]->isActive()) {
			if (ui_data[(*it)]->getUIType() == UITYPE::FontUI) {
				ci::gl::pushModelView();

				ci::gl::translate(0.0f, 0.0f, -3.0f);
				gl::drawString(ui_data[(*it)]->fontGetText(),
							   Vec2f(ui_data[(*it)]->getPosX(), ui_data[(*it)]->getPosY()),
							   Color(ui_data[(*it)]->getColorR(),
									 ui_data[(*it)]->getColorG(),
									 ui_data[(*it)]->getColorB()),
							   font[(*it)]);

				ci::gl::popModelView();
				continue;
			}
			if (ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
				ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
				ci::gl::pushModelView();

				ci::gl::translate(0.0f, 0.0f, -3.0f);
				gl::drawString(ui_data[(*it)]->timeGetMinutes() + ":" + ui_data[(*it)]->timeGetSeconds() + ":" + ui_data[(*it)]->timeGetFlame(),
							   Vec2f(ui_data[(*it)]->getPosX(), ui_data[(*it)]->getPosY()),
							   Color(ui_data[(*it)]->getColorR(),
									 ui_data[(*it)]->getColorG(),
									 ui_data[(*it)]->getColorB()),
							   font[(*it)]);

				ci::gl::popModelView();
				continue;
			}
			ci::gl::pushModelView();


			ci::gl::translate(0.0f, 0.0f, -3.0f);
			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
			TEX.get((*it)).enableAndBind();

			ci::gl::drawSolidRect(
				ci::Rectf(ci::Vec2f(
					ui_data[(*it)]->getPosX(),
					ui_data[(*it)]->getPosY()),
					ci::Vec2f(
						ui_data[(*it)]->getPosX() + ui_data[(*it)]->getSizeX(),
						ui_data[(*it)]->getPosY() + ui_data[(*it)]->getSizeY())));

			TEX.get((*it)).disable();

			ci::gl::popModelView();

			ci::gl::pushModelView();

			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());


			if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
				ci::gl::translate(0.0f, 0.0f, -1.0f);
				TEX.get(ui_data[(*it)]->gaugeGetTexturePath()).enableAndBind();
				ci::gl::drawSolidRect(
					ci::Rectf(ci::Vec2f(
						ui_data[(*it)]->gaugeGetPosX(),
						ui_data[(*it)]->gaugeGetPosY()),
						ci::Vec2f(
							ui_data[(*it)]->gaugeGetPosX() + ui_data[(*it)]->gaugeGetSizeX(),
							ui_data[(*it)]->gaugeGetPosY() + ui_data[(*it)]->gaugeGetSizeY())));
				TEX.get(ui_data[(*it)]->gaugeGetTexturePath()).disable();
			}
			ci::gl::popModelView();

		}
	}
	ci::gl::disableAlphaBlending();
	ci::gl::enableDepthRead();
}










void UIPlate::gameMainSetup()
{
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		if (ui_data[(*it)]->getUIType() == UITYPE::FontUI ||
			ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
			font[(*it)] = Font(ui_data[(*it)]->fontGetPath(), ui_data[(*it)]->fontGetSize());
			continue;
		}
		TEX.set((*it), ui_data[(*it)]->getTexturePath());
		if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
			TEX.set(ui_data[(*it)]->gaugeGetTexturePath(), ui_data[(*it)]->gaugeGetTexturePath());
		}
	}
	game_count = 0;
	ui_data["ダッシュゲージ"]->Active();

	ui_data["三"]->Active();
	ui_data["5位"]->Active();
	ui_data["Rank"]->Active();
	SoundGet.find("Count_1")->start();
	player->setIsStop(true);
}

void UIPlate::gameMainUpdate() {
	game_count++;
	if (game_count == 60) {
		ui_data["二"]->Active();
		SoundGet.find("Count_1")->stop();
		SoundGet.find("Count_1")->start();
	}
	if (game_count == 120) {
		ui_data["一"]->Active();
		SoundGet.find("Count_1")->stop();
		SoundGet.find("Count_1")->start();
	}
	if (game_count == 180) {
		ui_data["GO"]->Active();
		SoundGet.find("Count_1")->stop();
		SoundGet.find("Count_2")->start();
		player->setIsStop(false);
		enemyholder->start();
	}
	if (game_count == 240) {
		ui_data["制限時間"]->Active();
		ui_data["制限時間"]->timeStart();
	}

	switch (enemyholder->getRanking())
	{
	case 0:
		break;
	case 1:
		ui_data["2位"]->setEnd();
		ui_data["3位"]->setEnd();
		ui_data["4位"]->setEnd();
		ui_data["5位"]->setEnd();

		ui_data["1位"]->Active();
		break;
	case 2:
		ui_data["1位"]->setEnd();
		ui_data["3位"]->setEnd();
		ui_data["4位"]->setEnd();
		ui_data["5位"]->setEnd();

		ui_data["2位"]->Active();
		break;
	case 3:
		ui_data["2位"]->setEnd();
		ui_data["1位"]->setEnd();
		ui_data["4位"]->setEnd();
		ui_data["5位"]->setEnd();

		ui_data["3位"]->Active();
		break;
	case 4:
		ui_data["2位"]->setEnd();
		ui_data["3位"]->setEnd();
		ui_data["1位"]->setEnd();
		ui_data["5位"]->setEnd();

		ui_data["4位"]->Active();
		break;
	case 5:
		ui_data["2位"]->setEnd();
		ui_data["3位"]->setEnd();
		ui_data["4位"]->setEnd();
		ui_data["1位"]->setEnd();

		ui_data["5位"]->Active();
		break;
	}


	ui_data["制限時間"]->timeUpdate();


	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		ui_data[(*it)]->update();
	}
	ui_data["ダッシュゲージ"]->gaugeChangeX(0, 500.f);
	ui_data["OK"]->Idle();
	if (ui_data["ダッシュゲージ"]->gaugeGetIsMax()) {
		ui_data["OK"]->Active();
	}

}

void UIPlate::gameMainDraw() {
	ci::gl::disableDepthRead();
	ci::gl::enableAlphaBlending();
	ci::gl::setMatrices(camera_o);
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		if (ui_data[(*it)]->isActive()) {
			if (ui_data[(*it)]->getUIType() == UITYPE::FontUI) {
				ci::gl::pushModelView();

				ci::gl::translate(0.0f, 0.0f, -1.0f);
				gl::drawString(ui_data[(*it)]->fontGetText(),
							   Vec2f(ui_data[(*it)]->getPosX(), ui_data[(*it)]->getPosY()),
							   Color(ui_data[(*it)]->getColorR(),
									 ui_data[(*it)]->getColorG(),
									 ui_data[(*it)]->getColorB()),
							   font[(*it)]);

				ci::gl::popModelView();
				continue;
			}

			if (ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
				ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
				ci::gl::pushModelView();

				ci::gl::translate(0.0f, 0.0f, -3.0f);
				gl::drawString(ui_data[(*it)]->timeGetMinutes() + ":" + ui_data[(*it)]->timeGetSeconds() + ":" + ui_data[(*it)]->timeGetFlame(),
							   Vec2f(ui_data[(*it)]->getPosX(), ui_data[(*it)]->getPosY()),
							   Color(ui_data[(*it)]->getColorR(),
									 ui_data[(*it)]->getColorG(),
									 ui_data[(*it)]->getColorB()),
							   font[(*it)]);

				ci::gl::popModelView();
				continue;
			}
			ci::gl::pushModelView();


			ci::gl::translate(0.0f, 0.0f, -3.0f);
			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
			TEX.get((*it)).enableAndBind();
			ci::gl::drawSolidRect(
				ci::Rectf(ci::Vec2f(
					ui_data[(*it)]->getPosX(),
					ui_data[(*it)]->getPosY()),
					ci::Vec2f(
						ui_data[(*it)]->getPosX() + ui_data[(*it)]->getSizeX(),
						ui_data[(*it)]->getPosY() + ui_data[(*it)]->getSizeY())));
			TEX.get((*it)).disable();

			ci::gl::popModelView();

			ci::gl::pushModelView();

			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());


			if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
				ci::gl::translate(0.0f, 0.0f, -1.0f);
				TEX.get(ui_data[(*it)]->gaugeGetTexturePath()).enableAndBind();
				ci::gl::drawSolidRect(
					ci::Rectf(ci::Vec2f(
						ui_data[(*it)]->gaugeGetPosX(),
						ui_data[(*it)]->gaugeGetPosY()),
						ci::Vec2f(
							ui_data[(*it)]->gaugeGetPosX() + ui_data[(*it)]->gaugeGetSizeX(),
							ui_data[(*it)]->gaugeGetPosY() + ui_data[(*it)]->gaugeGetSizeY())));
				TEX.get(ui_data[(*it)]->gaugeGetTexturePath()).disable();
			}
			ci::gl::popModelView();

		}
	}
	ci::gl::disableAlphaBlending();
	ci::gl::enableDepthRead();
}

void UIPlate::resultSetup()
{
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		if (ui_data[(*it)]->getUIType() == UITYPE::FontUI ||
			ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
			font[(*it)] = Font(ui_data[(*it)]->fontGetPath(), ui_data[(*it)]->fontGetSize());
			continue;
		}
		TEX.set((*it), ui_data[(*it)]->getTexturePath());
		if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
			TEX.set(ui_data[(*it)]->gaugeGetTexturePath(), ui_data[(*it)]->gaugeGetTexturePath());
		}
	}
	ui_data["GOAL"]->Active();

}

void UIPlate::resultUpdate()
{
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		ui_data[(*it)]->update();
	}
}

void UIPlate::resultDraw()
{
	ci::gl::enableAlphaBlending();
	ci::gl::setMatrices(camera_o);
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		if (ui_data[(*it)]->isActive()) {
			if (ui_data[(*it)]->getUIType() == UITYPE::FontUI) {
				ci::gl::pushModelView();

				ci::gl::translate(0.0f, 0.0f, -1.0f);
				gl::drawString(ui_data[(*it)]->fontGetText(),
							   Vec2f(ui_data[(*it)]->getPosX(), ui_data[(*it)]->getPosY()),
							   Color(ui_data[(*it)]->getColorR(),
									 ui_data[(*it)]->getColorG(),
									 ui_data[(*it)]->getColorB()),
							   font[(*it)]);

				ci::gl::popModelView();
				continue;
			}

			if (ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
				ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
				ci::gl::pushModelView();

				ci::gl::translate(0.0f, 0.0f, -3.0f);
				gl::drawString(ui_data[(*it)]->timeGetMinutes() + ":" + ui_data[(*it)]->timeGetSeconds() + ":" + ui_data[(*it)]->timeGetFlame(),
							   Vec2f(ui_data[(*it)]->getPosX(), ui_data[(*it)]->getPosY()),
							   Color(ui_data[(*it)]->getColorR(),
									 ui_data[(*it)]->getColorG(),
									 ui_data[(*it)]->getColorB()),
							   font[(*it)]);

				ci::gl::popModelView();
				continue;
			}
			ci::gl::pushModelView();


			ci::gl::translate(0.0f, 0.0f, -3.0f);
			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
			TEX.get((*it)).enableAndBind();
			ci::gl::drawSolidRect(
				ci::Rectf(ci::Vec2f(
					ui_data[(*it)]->getPosX(),
					ui_data[(*it)]->getPosY()),
					ci::Vec2f(
						ui_data[(*it)]->getPosX() + ui_data[(*it)]->getSizeX(),
						ui_data[(*it)]->getPosY() + ui_data[(*it)]->getSizeY())));
			TEX.get((*it)).disable();

			ci::gl::popModelView();

			ci::gl::pushModelView();

			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());


			if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
				ci::gl::translate(0.0f, 0.0f, -1.0f);
				TEX.get(ui_data[(*it)]->gaugeGetTexturePath()).enableAndBind();
				ci::gl::drawSolidRect(
					ci::Rectf(ci::Vec2f(
						ui_data[(*it)]->gaugeGetPosX(),
						ui_data[(*it)]->gaugeGetPosY()),
						ci::Vec2f(
							ui_data[(*it)]->gaugeGetPosX() + ui_data[(*it)]->gaugeGetSizeX(),
							ui_data[(*it)]->gaugeGetPosY() + ui_data[(*it)]->gaugeGetSizeY())));
				TEX.get(ui_data[(*it)]->gaugeGetTexturePath()).disable();
			}
			ci::gl::popModelView();

		}
	}
	ci::gl::disableAlphaBlending();
}
