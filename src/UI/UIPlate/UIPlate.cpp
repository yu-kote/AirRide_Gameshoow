#include "UIPlate.h"

void UIPlate::titleSetup()
{
	
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		TEX.set((*it), ui_data[(*it)]->getTexturePath());
		if (ui_data[(*it)]->isGaugeUI()) {
			TEX.set(ui_data[(*it)]->getGaugeTexturePath(), ui_data[(*it)]->getGaugeTexturePath());
		}
	}
	ui_data["プレイヤーポジション"]->Active();
	ui_data["ダッシュゲージ"]->Active();
	ui_data["ポジションバー"]->Active();
	
	ci::gl::enableAlphaBlending();
}
float a = 0;
void UIPlate::titleUpdate() {
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		ui_data[(*it)]->update();
	}
	a++;
	ui_data["ダッシュゲージ"]->changeGauge(a,500.f);
	/*if (ui_data["オプション"]->NextFlag() || ui_data["スタート"]->NextFlag()) {
	if (ui_data["タイトル"]->collisionToUI(des::Vec2f(event.getX(), event.getY()))) {
	ui_data["タイトル"]->setEnd();
	ui_data["オプション"]->Active();
	ui_data["スタート"]->Active();
	}
	}

	if (ui_data["タイトル"]->NextFlag()) {
	if (ui_data["オプション"]->collisionToUI(des::Vec2f(event.getX(), event.getY())) ||
	ui_data["スタート"]->collisionToUI(des::Vec2f(event.getX(), event.getY()))) {
	ui_data["オプション"]->setEnd();
	ui_data["スタート"]->setEnd();
	ui_data["タイトル"]->Active();
	}
	}*/
}

void UIPlate::titleDraw() {
	
	
	ci::gl::setMatrices(camera_o);
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
	

		ci::gl::pushModelView();
		
		ci::gl::color(ui_data[(*it)]->getColorR(),ui_data[(*it)]->getColorG(),ui_data[(*it)]->getColorB(),ui_data[(*it)]->getColorA());
		ci::gl::translate(0.0f, 0.0f, -3.0f);
		
		
		
		

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
		ci::gl::translate(0.0f, 0.0f, -1.0f);

		if (ui_data[(*it)]->isGaugeUI()) {
			TEX.get(ui_data[(*it)]->getGaugeTexturePath()).enableAndBind();
			ci::gl::drawSolidRect(
				ci::Rectf(ci::Vec2f(
					ui_data[(*it)]->getGaugePosX(),
					ui_data[(*it)]->getGaugePosY()),
					ci::Vec2f(
						ui_data[(*it)]->getGaugePosX() + ui_data[(*it)]->getGaugeSizeX(),
						ui_data[(*it)]->getGaugePosY() + ui_data[(*it)]->getGaugeSizeY())));
			TEX.get(ui_data[(*it)]->getGaugeTexturePath()).disable();
		
		}
		ci::gl::popModelView();
		
	}
	
}














void UIPlate::gameMainSetup()
{
}

void UIPlate::gameMainUpdate()
{
}

void UIPlate::gameMainDraw()
{
}
