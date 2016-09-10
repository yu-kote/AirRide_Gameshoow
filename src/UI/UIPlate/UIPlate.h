#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/svg/Svg.h"
#include "cinder/imageIo.h" 
#include "cinder/gl/Texture.h" 
#include "../UIManager/UIManager.h"
#include "cinder/Camera.h"
#include "../Texture.h"
#include "../../Object/GameObject/CharaBase/Player/Player.h"
#include "../../Object/GameObject/CharaBase/Enemy/EnemyHolder/EnemyHolder.h"
#include "../../Object/GameObject/Boss/Boss.h"

class UIPlate : public UIManager
{
private:
	ci::CameraOrtho camera_o;
	ci::gl::Texture tex;
	std::unordered_map<std::string, Font> font;
	int game_count;
	int tuto_count;
	int change_counnt;
	int rank_in;
	int goal_count;
	int boss_count;
public:
	UIPlate() {
		camera_o = ci::CameraOrtho(0, 800,
								   600, 0,
								   1, 10);
		camera_o.setEyePoint(ci::Vec3f(0.0f, 0.0f, 0.0f));
		camera_o.setCenterOfInterestPoint(ci::Vec3f(0.0f, 0.0f, -1000.0f));
	};
	void titleSetup();
	void titleUpdate();
	void titleDraw();
	void tuto1();
	void tuto2();
	void tuto3();
	void tuto4(bool &end_flag);

	void gameMainSetup();
	void gameMainUpdate();
	void gameMainDraw();
	void gameMainTimeWrite();
	void gameMainShift();
	void gameMainBossActive();
	void gameMainTimeUp();

	void resultSetup();
	void endingSetup();
	void resultUpdate();
	void resultDraw();

	std::shared_ptr<Player> player;
	std::shared_ptr<EnemyHolder> enemyholder;
	std::shared_ptr<Boss> boss;
};