#include "Title.h"
#include "../SceneCategory/GameMain.h"
#include "../../Input/InputEvent.h"
#include "../../Input/LeapMotion/LeapHands/LeapHands.h"

#include "../../Object/GameObject/Light/Light.h"
#include "../../Object/GameObject/Camera/Camera.h"
#include "../../Object/GameObject/SignPost/SignPostManager.h"
#include "../../Object/GameObject/Obstacle/ObstacleManager.h"
#include "../../Object/GameObject/CharaBase/Player/Player.h"
#include "../../Object/GameObject/CharaBase/Enemy/Enemy.h"
#include "../../Object/GameObject/CharaBase/Enemy/EnemyHolder/EnemyHolder.h"
#include "../../Share/Interface/Interface.h"
#include "../../Object/GameObject/Skydome/Skydome.h"
#include "../../Object/GameObject/Boss/Boss.h"
#include "../../Object/GameObject/Boss/Bullet/Bullet.h"
#include "../../TaskManager/SoundManager.h"

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
	tutorial = false;
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

			gameSetup();
			ui.player = entities.getObject<Player>();
			if (SoundGet.find("TitleBGM")->isEnabled())
				SoundGet.find("TitleBGM")->stop();
			else
				SoundGet.find("TitleBGM")->start();
			SoundGet.find("TitleBGM")->setLoopEnabled(true);
		}
		ui.titleUpdate();
		gameUpdate();
		//bool set1
		//bool set2
		//bool set3
		//↓のif文の中で引数をtrueにする
		if (ui.getTutoFirtsFlag()) {
			if (LEAPHANDS.GetHandCenterPosToRatio().y >= 0.13f
				|| env.isPress(KeyEvent::KEY_0)) {
				tutorial_flag[0] = true;
			}
		}
		if (ui.getTutoSecondFlag()) {
			if (player->isCharaDashing())
				tutorial_flag[1] = true;
		}
		if (ui.getTutoThirdFlag()
			&& env.isPress(KeyEvent::KEY_9)) {
				tutorial_flag[2] = true;
		}
	}
	if (end_flag == true &&
		end_count == 1) {
		ui.ui_data["黒板"]->Active();
		ui.ui_data["黒板"]->setEnd();
	}

	

	if (tutorial) {

		ui.tuto1(tutorial_flag[0]);

		if (tutorial_flag[0]) {
			ui.tuto2(tutorial_flag[1]);
		}
		if (tutorial_flag[1]) {
			ui.tuto3(tutorial_flag[2]);
		}
		if (tutorial_flag[2]) {
			ui.tuto4(end_flag);
		}
	}
	if (env.isPush(KeyEvent::KEY_BACKSPACE)) {
		SoundGet.find("TitleBGM")->stop();
		SoundGet.find("Start")->start();
		end_flag = true;
	}

}

void Title::draw()
{
	if (!UIType::is_loop) {
		gameDraw();
		ui.titleDraw();
		gl::popMatrices();

		//ci::gl::clear(ColorA(color_r, color_g, color_b, 1.0f));

	}
	else {
		setup();
		UIType::is_loop = false;
	}

	//gl::popMatrices();

}

void Title::shift()
{
	if (update_count >= 1) {
		if (tutorial == false) {
			if (env.isPress(KeyEvent::KEY_RETURN) ||
				LEAPHANDS.IsHandExist())
			{
				ui.ui_data["開始ゲージ"]->Active();
				next_count += 1;
			}
			else {
				ui.ui_data["開始ゲージ"]->Idle();
				next_count = 0;
			}


			ui.ui_data["開始ゲージ"]->gaugeChangeX(next_count, 60);
		}
		else {
			ui.ui_data["開始ゲージ"]->Idle();
			ui.ui_data["開始ゲージ"]->gaugeChangeX(0, 60);
		}
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
			ui.ui_data["白板"]->setEnd();
			ui.ui_data["黒板"]->Active();
			ui.ui_data["黒板"]->setColor(1, 1, 1, 0);
			ui.ui_data["黒板"]->setEnd();
			ui.ui_data["開始ゲージ"]->Idle();
			ui.ui_data["スタート"]->setEnd();
			tutorial = true;
			SoundGet.find("Start")->start();

		}
	}

	if (end_count >= 100) {
		c_Easing::clear(color_r);
		c_Easing::clear(color_g);
		c_Easing::clear(color_b);
		UIType::erase();
		UIObjects::erase();
		UIState::erase();
		EasingType::erase();

		Params->clear();

		Scene::createScene<GameMain>(new GameMain());
	}

}

void Title::shutdown()
{
	entities.Alldestroy();
}

void Title::gameSetup()
{
	entities.setObject<ar::Light>();
	entities.setObject<ar::Camera>();

	///////////////////////////////////////////////

	entities.setObject<ar::Skydome>();
	entities.setObject<ar::SignPostManager>();
	//entities.setObject<ar::ObstacleManager>();

	entities.setObject<Player>();
	//entities.setObject<EnemyHolder>();

	//entities.setObject<Boss>();
	//entities.setObject<Bullets>();


	//////////////////////////////////////////////

	entities.getObject<Player>()->setSignPostManager(entities.getObject<ar::SignPostManager>());
	entities.getObject<ar::SignPostManager>()->setPlayer(entities.getObject<Player>());


	//entities.getObject<EnemyHolder>()->setSignPostManager(entities.getObject<ar::SignPostManager>());
	//entities.getObject<EnemyHolder>()->setPlayer(entities.getObject<Player>());

	//entities.getObject<ar::ObstacleManager>()->setEnemyHolder(entities.getObject<EnemyHolder>());
	//entities.getObject<ar::ObstacleManager>()->setPlayer(entities.getObject<Player>());

	entities.getObject<ar::Camera>()->setChara(entities.getObject<Player>());

	entities.getObject <ar::Skydome>()->setTerget(entities.getObject<Player>());

	//entities.getObject <Boss>()->setSignPostManager(entities.getObject<ar::SignPostManager>());
	//entities.getObject <Boss>()->setEnemyHolder(entities.getObject<EnemyHolder>());
	//entities.getObject <Boss>()->setPlayer(entities.getObject<Player>());

	//entities.getObject <Bullets>()->setBoss(entities.getObject<Boss>());
	//entities.getObject <Bullets>()->setPlayer(entities.getObject<Player>());

	//entities.getObject<ar::ObstacleManager>()->setBoss(entities.getObject<Boss>());

	entities.setupGameObject();

	player = entities.getObject<Player>();
}

void Title::gameUpdate()
{
	entities.updateGameObject();
	entities.laterUpdateGameObject();
}

void Title::gameDraw()
{
	//entities.getObject<ar::ObstacleManager>()->setCameraPos(entities.getObject<ar::Camera>()->getCenterOfInterestPoint());

	entities.drawGameObject();
	entities.transDrawGameObject();

	// ライトがない描画
	entities.laterDrawGameObject();
	entities.transLaterDrawGameObject();
}
