#include "UIPlate.h"
#include "../src/Input/LeapMotion/LeapHands/LeapHands.h"
#include "../../Share/Resize.h"
#include "../../Share/Share.h"
#include "../../Share/Interface/Interface.h"
#include "../../Scene/SceneCategory/Result.h"
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


	for (int i = 0; i < 14; i++) {
		tuto_count[i] = 0;
	}
	for (int i = 0; i < 3; i++) {
		tuto_flags[i] = false;
	}
	change_counnt = 0;
	ui_data["白板"]->Active();
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

void UIPlate::tuto1(const bool& end_flag)
{
	if (end_flag == false) {
		if (ui_data["黒板"]->isActive()) {
			tuto_count[8]++;
			if (tuto_count[8] == 60) {
				player->restart();
			}
		}
		if (!ui_data["黒板"]->isActive()) {

			tuto_count[0]++;
			if (tuto_count[0] == 1) {
				ui_data["中央白板"]->Active();
			}
		}

		if (tuto_count[0] == 40) {
			ui_data["操作説明"]->Active();
			ui_data["操作説明"]->setColor(1, 0, 0, 1);
			ui_data["操作説明"]->fontSetText(u8"操作説明");
		}
		if (tuto_count[0] == 200) {
			ui_data["中央白板"]->setEnd();
		}
		if (tuto_count[0] == 280) {
			ui_data["ミッション白板"]->Active();
		}
		if (tuto_count[0] == 340) {
			ui_data["動き説明2"]->Active();
			ui_data["動き説明2"]->fontSetText(u8"自機はプレイヤーの手を追尾します。\n　手を上まで動かしてみてください。");
			ui_data["動き実手"]->Active();
			tuto_flags[0] = true;
		}
	}
	else if (end_flag == true) {
		tuto_count[1]++;
		if (tuto_count[1] == 1) {
			ui_data["TutorialOK"]->Active();
			ui_data["TutorialOK"]->setEnd();
			SoundGet.find("Start")->start();
			ui_data["動き実手"]->setEnd();
			ui_data["動き説明2"]->setEnd();
			ui_data["ミッション白板"]->setEnd();
			ui_data["黒板"]->Active();
			ui_data["黒板"]->setEnd();
		}
	}
}

void UIPlate::tuto2(const bool& end_flag)
{
	if (end_flag == false) {
		if (ui_data["黒板"]->isActive()) {
			tuto_count[9]++;
			if (tuto_count[9] == 60) {
				player->restart();
			}
		}
		if (!ui_data["黒板"]->isActive()) {
			tuto_count[2]++;
			if (tuto_count[2] == 1) {
				ui_data["ミッション白板"]->Active();
			}
		}
		if (tuto_count[2] == 60) {
			ui_data["ダッシュ説明2"]->Active();
			ui_data["ダッシュ説明2"]->fontSetText(u8"手を前に突き出すと、突進します。\n　実際にやってみましょう。");
			ui_data["ダッシュ手"]->Active();
			tuto_flags[1] = true;
		}
	}
	else if (end_flag == true) {
		tuto_count[3]++;
		if (tuto_count[3] == 1) {
			ui_data["TutorialOK"]->Active();
			ui_data["TutorialOK"]->setEnd();
			SoundGet.find("Start")->start();
			ui_data["ダッシュ手"]->setEnd();
			ui_data["ダッシュ説明2"]->setEnd();
			ui_data["ミッション白板"]->setEnd();
			ui_data["黒板"]->Active();
			ui_data["黒板"]->setEnd();
		}
	}
}

void UIPlate::tuto3(const bool& end_flag)
{
	if (end_flag == false) {
		if (ui_data["黒板"]->isActive()) {
			tuto_count[10]++;
			if (tuto_count[10] == 60) {
				player->restart();

			}
		}
		if (!ui_data["黒板"]->isActive()) {
			tuto_count[4]++;
			if (tuto_count[4] == 1) {
				ui_data["ミッション白板"]->Active();
			}
		}
		if (tuto_count[4] == 60) {
			ui_data["回避説明2"]->Active();
			ui_data["回避説明2"]->fontSetText(u8"それでは、敵を突進で倒してみましょう。");
			ui_data["回避説明"]->Active();
			ui_data["回避説明"]->fontSetText(u8"　赤い所で突進してください。");
			ui_data["丸"]->Active();
			tuto_flags[2] = true;
		}
	}
	else if (end_flag == true) {
		tuto_count[5]++;
		if (tuto_count[5] == 1) {
			ui_data["TutorialOK"]->Active();
			ui_data["TutorialOK"]->setEnd();
			SoundGet.find("Start")->start();
			ui_data["回避説明2"]->setEnd();
			ui_data["ミッション白板"]->setEnd();
			ui_data["回避説明"]->setEnd();
			ui_data["丸"]->setEnd();
			ui_data["黒板"]->Active();
			ui_data["黒板"]->setEnd();
			ui_data["操作説明"]->setEnd();
		}
	}
}

void UIPlate::tuto4(bool &end_flag)
{
	if (ui_data["黒板"]->isActive()) {
		tuto_count[11]++;
		if (tuto_count[11] == 60) {
			player->restart();
		}
	}
	if (!ui_data["操作説明"]->isActive()) {
		change_counnt++;
		if (change_counnt == 1) {
			ui_data["ゲーム説明"]->Active();
			ui_data["説明板"]->Active();
			ui_data["ミッション白板"]->Active();
			ui_data["ゲーム説明"]->fontSetText(u8"障害物を避けながら、\nエネミーを突進で倒しましょう！");
		}
		if (change_counnt == 240) {
			ui_data["ゲーム説明"]->setEnd();
			ui_data["説明板"]->setEnd();
		}
		if (change_counnt == 300) {
			ui_data["ゲーム説明2"]->Active();
			ui_data["ゲーム説明2"]->fontSetText(u8"チュートリアルは以上です。\n　頑張って下さいね！");
		}
		if (change_counnt == 500) {
			ui_data["ゲーム説明2"]->setEnd();
			ui_data["ミッション白板"]->setEnd();
			SoundGet.find("TitleBGM")->disable();
			end_flag = true;
		}
	}

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
	goal_count = 0;
	boss_count = 0;
	ui_data["GameMainChange"]->Active();
	ui_data["GameMainChange"]->setEnd();
	ui_data["ダッシュゲージ"]->Active();
	ui_data["ResultChange1"]->Active();
	ui_data["5位"]->Active();
	ui_data["Rank"]->Active();
	ui_data["体"]->Active();
	player->setIsStop(true);
}

void UIPlate::gameMainUpdate() {
	if (!ui_data["GameMainChange"]->isActive()) {
		game_count++;
		if (game_count == 1) {
			ui_data["三"]->Active();
			SoundGet.find("Count_1")->start();
		}
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
			if (SoundGet.find("RaceBGM")->isEnabled())
				SoundGet.find("RaceBGM")->stop();
			else
				SoundGet.find("RaceBGM")->start();
			SoundGet.find("RaceBGM")->setLoopEnabled(true);
		}
	}
	if (!boss->getIsExist()) {
		switch (enemyholder->remainingEnemy())
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
	}

	ui_data["制限時間"]->timeUpdate();
	ui_data["経過時間"]->timeUpdate();

	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		ui_data[(*it)]->update();
	}
	ui_data["ダッシュゲージ"]->gaugeChangeX(player->getIntervalCount(), 1.0f);
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

void UIPlate::gameMainTimeWrite()
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

void UIPlate::gameMainShift() {
	goal_count++;
	if (goal_count == 1) {
		SoundGet.find("BattleBGM")->disable();
		SoundGet.find("Goal")->start();
		ui_data["Goal"]->Active();
		ui_data["Goal2"]->Active();
	}
	if (goal_count == 150) {
		ui_data["Goal"]->setEnd();
		ui_data["Goal2"]->setEnd();
	}
	if (goal_count == 180) {
		ui_data["ResultChange1"]->setEnd();
	}
}

void UIPlate::gameMainBossActive()
{
	if (boss->getIsExist()) {
		ui_data["制限時間"]->Idle();
		boss_count++;
		if (boss_count == 1) {
			ui_data["ボスゲージ"]->Active();
		}
		if (boss_count / 10 <= boss->getHp()) {
			ui_data["ボスゲージ"]->gaugeChangeX(boss_count / 10, boss->getMaxHp());
		}
		else {
			ui_data["ボスゲージ"]->gaugeChangeX(boss->getHp(), boss->getMaxHp());
		}
		if (boss_count <= 30) {
			SoundGet.find("RaceBGM")->gain->setValue(1.0f - ((static_cast<float>(boss_count) / 30)));
		}
		if (boss_count == 30) {
			SoundGet.find("Boss")->start();
			ui_data["ボス出現"]->Active();
			ui_data["ボス出現"]->setEnd();
		}
		if (boss_count == 300) {
			if (SoundGet.find("BattleBGM")->isEnabled())
				SoundGet.find("BattleBGM")->stop();
			else
				SoundGet.find("BattleBGM")->start();
			SoundGet.find("BattleBGM")->setLoopEnabled(true);
		}
	}
}

void UIPlate::gameMainTimeUp()
{
	if (!boss->getIsExist()) {
		if (ui_data["制限時間"]->timeOver()) {
			boss_count++;
			if (boss_count == 1) {
				SoundGet.find("RaceBGM")->disable();
				SoundGet.find("TimeUp")->start();
				ui_data["タイムアップ"]->Active();
				ui_data["TimeUpChange"]->Active();
				ui_data["TimeUpChange"]->setColor(1, 1, 1, 0);
				ui_data["TimeUpChange"]->setEnd();
			}
			if (!ui_data["TimeUpChange"]->isActive()) {
				UIType::is_ending = true;
				UIType::erase();
				UIObjects::erase();
				UIState::erase();
				EasingType::erase();
				ui_data.clear();
				Scene::createScene<Result>(new Result());
			}
		}
	}
}

void UIPlate::gameMainTimeRed()
{
	if (std::stoi(ui_data["制限時間"]->timeGetMinutes()) < 1) {
		if (std::stoi(ui_data["制限時間"]->timeGetSeconds()) < 40) {
			ui_data["制限時間"]->setColor(1, 1, 0, 1);
		}
		if (std::stoi(ui_data["制限時間"]->timeGetSeconds()) < 20) {
			ui_data["制限時間"]->setColor(1, 0, 0, 1);
		}
		if (std::stoi(ui_data["制限時間"]->timeGetSeconds()) < 10) {
			if (std::stoi(ui_data["制限時間"]->timeGetFlame()) % 20 >= 10) {
				ui_data["制限時間"]->setColor(1, 1, 1, 1);
			}
			else if (std::stoi(ui_data["制限時間"]->timeGetFlame()) % 20 <= 10) {
				ui_data["制限時間"]->setColor(1, 0, 0, 1);
			}
		}
		if (std::stoi(ui_data["制限時間"]->timeGetSeconds()) < 5) {
			if (std::stoi(ui_data["制限時間"]->timeGetFlame()) % 10 >= 5) {
				ui_data["制限時間"]->setColor(1, 1, 1, 1);
			}
			else if (std::stoi(ui_data["制限時間"]->timeGetFlame()) % 10 <= 5) {
				ui_data["制限時間"]->setColor(1, 0, 0, 1);
			}
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

	float left = -(getWindowSize().x - WIDTH) / 2;
	float right = 800 + (getWindowSize().x - WIDTH) / 2;
	float bottom = -(getWindowSize().y - WIDTH) / 2;
	float top = 800 + (getWindowSize().y - WIDTH) / 2;
	camera_o.setOrtho(left, right,
					  600, 0,
					  1, 10);

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
		ui_data["リザルト"]->Active();
		ui_data["Rank1"]->fontSetText("1st " + std::to_string(time[0].minutes) + "'" + addZero(time[0].seconds) + "''" + addZero(time[0].flame));
		ui_data["Rank2"]->fontSetText("2nd " + std::to_string(time[1].minutes) + "'" + addZero(time[1].seconds) + "''" + addZero(time[1].flame));
		ui_data["Rank3"]->fontSetText("3rd " + std::to_string(time[2].minutes) + "'" + addZero(time[2].seconds) + "''" + addZero(time[2].flame));
		ui_data["Rank4"]->fontSetText("4th " + std::to_string(time[3].minutes) + "'" + addZero(time[3].seconds) + "''" + addZero(time[3].flame));
		ui_data["Rank5"]->fontSetText("5th " + std::to_string(time[4].minutes) + "'" + addZero(time[4].seconds) + "''" + addZero(time[4].flame));
		ui_data["ResultTime"]->fontSetText(u8"今回のタイム　" + std::to_string(time[5].minutes) + "'" + addZero(time[5].seconds) + "''" + addZero(time[5].flame));
		ui_data["ResultTime"]->setColor(0.5, 0.5, 1, 1);
		ui_data["ResultChange2"]->Active();
		ui_data["ResultChange2"]->setEnd();
	}
}

void UIPlate::endingSetup()
{
	setup();

	float left = -(getWindowSize().x - WIDTH) / 2;
	float right = 800 + (getWindowSize().x - WIDTH) / 2;
	float bottom = -(getWindowSize().y - WIDTH) / 2;
	float top = 800 + (getWindowSize().y - WIDTH) / 2;
	camera_o.setOrtho(left, right,
					  600, 0,
					  1, 10);

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
}

void UIPlate::resultUpdate()
{

	float left = -(getWindowSize().x - WIDTH) / 2;
	float right = 800 + (getWindowSize().x - WIDTH) / 2;
	float bottom = -(getWindowSize().y - WIDTH) / 2;
	float top = 800 + (getWindowSize().y - WIDTH) / 2;
	camera_o.setOrtho(left, right,
					  600, 0,
					  1, 10);

	game_count++;
	ui_data["ResultTime"]->setColor(0, 0, 0.5 + std::sinf(game_count / 4) / 2, 1);
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		ui_data[(*it)]->update();
	}
	switch (rank_in) {
	case 1:
		ui_data["Rank1"]->setColor(1.0f, 0.5f, std::sinf(game_count), 1.0f);
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

