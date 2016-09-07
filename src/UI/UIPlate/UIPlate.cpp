#include "UIPlate.h"
#include "../src/Input/LeapMotion/LeapHands/LeapHands.h"
#include "../../Share/Resize.h"
#include "../../Share/Share.h"
std::string addZero(const int& value) {
	if (value < 10) {
		return "0" + std::to_string(value);
	}
	return std::to_string(value);
}
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
	setup();
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
	ui_data["ResultChange1"]->Active();
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
		ui_data["経過時間"]->Active();
		ui_data["経過時間"]->timeStart();
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
	ui_data["経過時間"]->timeUpdate();
	if (ui_data["制限時間"]->timeOver()) {

	}

	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		ui_data[(*it)]->update();
	}
	ui_data["ダッシュゲージ"]->gaugeChangeX(player->getDashCount(), 1.0f);
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
				gl::drawString(ui_data[(*it)]->timeGetMinutes() + "'" + ui_data[(*it)]->timeGetSeconds() + "''" + ui_data[(*it)]->timeGetFlame(),
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
	ci::gl::popModelView();
}

void UIPlate::gameMainShift()
{
	{
		ui_data["経過時間"]->timeStop();
		{
			std::ifstream file(ci::app::getAssetPath("UI/SaveData/SaveData.txt").string());
			assert(file);
			int count;
			int rank = 0;
			struct Time {
				int minutes;
				int seconds;
				int flame;
			};
			Time time[7];
			time[5].minutes = std::stoi(ui_data["経過時間"]->timeGetMinutes());
			time[5].seconds = std::stoi(ui_data["経過時間"]->timeGetSeconds());
			time[5].flame = std::stoi(ui_data["経過時間"]->timeGetFlame());
			file >> count;
			for (int i = 0; i < count; i++) {
				file >> time[i].minutes;
				file >> time[i].seconds;
				file >> time[i].flame;
			}
			for (int i = 0; i < count; i++) {
				int top_score = (time[i].minutes * 3600) + (time[i].seconds * 60) + time[i].flame;
				int now_score = (time[5].minutes * 3600) + (time[5].seconds * 60) + time[5].flame;
				if (top_score >= now_score) {
					if (rank > 0) {
						std::swap(time[6].minutes, time[i].minutes);
						std::swap(time[6].seconds, time[i].seconds);
						std::swap(time[6].flame, time[i].flame);
						continue;
					}
					time[6].minutes = time[i].minutes;
					time[6].seconds = time[i].seconds;
					time[6].flame = time[i].flame;
					time[i].minutes = time[5].minutes;
					time[i].seconds = time[5].seconds;
					time[i].flame = time[5].flame;
					rank = i + 1;

				}
			}
			std::ofstream out_file(ci::app::getAssetPath("UI/SaveData/SaveData.txt").string());
			out_file << 5 << std::endl;
			for (int i = 0; i < 6; i++) {
				out_file << time[i].minutes << ' ' << time[i].seconds << ' ' << time[i].flame << std::endl;
			}
			out_file << rank;
		}
		
	}
}

void UIPlate::resultSetup()
{
	setup();
	game_count = 0;
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


	{
		std::ifstream file(ci::app::getAssetPath("UI/SaveData/SaveData.txt").string());
		assert(file);
		int count;
		struct Time {
			int minutes;
			int seconds;
			int flame;
		};
		Time time[6];
		time[5].minutes = std::stoi(ui_data["経過時間"]->timeGetMinutes());
		time[5].seconds = std::stoi(ui_data["経過時間"]->timeGetSeconds());
		time[5].flame = std::stoi(ui_data["経過時間"]->timeGetFlame());
		file >> count;
		count += 1;
		for (int i = 0; i < count; i++) {
			file >> time[i].minutes;
			file >> time[i].seconds;
			file >> time[i].flame;
		}
		file >> rank_in;
		ui_data["Rank1"]->Active();
		ui_data["Rank2"]->Active();
		ui_data["Rank3"]->Active();
		ui_data["Rank4"]->Active();
		ui_data["Rank5"]->Active();
		ui_data["ResultTime"]->Active();
		ui_data["Rank1"]->fontSetText("1st " + std::to_string(time[0].minutes) + "'" + addZero(time[0].seconds) + "''" + addZero(time[0].flame));
		ui_data["Rank2"]->fontSetText("2nd " + std::to_string(time[1].minutes) + "'" + addZero(time[1].seconds) + "''" + addZero(time[1].flame));
		ui_data["Rank3"]->fontSetText("3rd " + std::to_string(time[2].minutes) + "'" + addZero(time[2].seconds) + "''" + addZero(time[2].flame));
		ui_data["Rank4"]->fontSetText("4th " + std::to_string(time[3].minutes) + "'" + addZero(time[3].seconds) + "''" + addZero(time[3].flame));
		ui_data["Rank5"]->fontSetText("5th " + std::to_string(time[4].minutes) + "'" + addZero(time[4].seconds) + "''" + addZero(time[4].flame));
		ui_data["ResultTime"]->fontSetText(u8"今回のタイム　" + std::to_string(time[5].minutes) + "'" + addZero(time[5].seconds) + "''" + addZero(time[5].flame));
		ui_data["ResultChange2"]->Active();
		ui_data["ResultChange2"]->setEnd();
	}
}

void UIPlate::resultUpdate()
{
	game_count++;
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		ui_data[(*it)]->update();
	}
	if (!ui_data["ResultChange2"]->isActive()) {
		ui_data["リザルト"]->Active();
	}
	switch (rank_in) {
	case 1: 
		ui_data["Rank1"]->setColor(1.0f, 0.5f, std::sinf(game_count),1.0f);
		break;
	case 2:
		ui_data["Rank2"]->setColor(std::sinf(game_count), std::sinf(game_count), std::sinf(game_count), 1.0f);
		break;
	case 3:
		ui_data["Rank3"]->setColor(std::sinf(game_count), std::sinf(game_count), std::sinf(game_count), 1.0f);
		break;
	case 4:
		ui_data["Rank4"]->setColor(std::sinf(game_count), std::sinf(game_count), std::sinf(game_count), 1.0f);
		break;
	case 5:
		ui_data["Rank5"]->setColor(std::sinf(game_count), std::sinf(game_count), std::sinf(game_count), 1.0f);
		break;
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

