#include "UIPlate.h"

void UIPlate::update() {

}

void UIPlate::draw() {
	
	/*	ci::gl::pushModelView();
		ci::gl::translate(0.0f, 0.0f, -5.0f);
		
		ci::gl::enableAlphaBlending();

		texture.enableAndBind();
		
		ci::gl::drawSolidRect(ci::Rectf(v2_pos,end_pos));

		texture.disable();
		ci::gl::disableAlphaBlending();
		ci::gl::popModelView();*/
	ci::gl::setMatrices(camera_o);
	for (auto it = UIObjects::get().begin(); it != UIObjects::get().end(); it++) {
		ci::gl::pushModelView();
		ci::gl::translate(0.0f, 0.0f, -9.0f);

		ci::gl::enableAlphaBlending();
		ci::gl::drawSolidRect(ci::Rectf(ci::Vec2f(ui.ui_data[(*it)]->getPosX(),
			ui.ui_data[(*it)]->getPosY()),
			ci::Vec2f(ui.ui_data[(*it)]->getPosX() + ui.ui_data[(*it)]->getSizeX(),
				ui.ui_data[(*it)]->getPosY() + ui.ui_data[(*it)]->getSizeY())));
		ci::gl::disableAlphaBlending();
		ci::gl::popModelView();

	}

}