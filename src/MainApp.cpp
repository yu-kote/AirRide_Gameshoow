#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder/gl/Light.h"        // ���C�e�B���O
#include "cinder/gl/Material.h"     // �}�e���A��(�ގ�)

#include "Share/Share.h"
#include "Share/FrameTimer.h"
#include "Input/InputEvent.h"
#include "Scene/SceneManager/SceneManager.h"
#include "Share/Easing/Easing.h"


using namespace ci;
using namespace ci::app;
using namespace std;

#include <vector>

class DesignApp : public AppNative {
public:

	void keyDown(KeyEvent event) override;
	void keyUp(KeyEvent event) override;
	void mouseDown(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;

	void setup() override;
	void prepareSettings(Settings* settings) override;

	void update() override;
	void draw() override;

	void shutdown();

private:

	SceneManager scene;

	FrameTimer timer;
};

void DesignApp::keyDown(KeyEvent event)
{
	env.keyDown(event);
}

void DesignApp::keyUp(KeyEvent event)
{
	env.keyUp(event);
}

void DesignApp::mouseDown(MouseEvent event)
{
	env.mouseDown(event);
}

void DesignApp::mouseUp(MouseEvent event)
{
	env.mouseUp(event);
}

void DesignApp::setup()
{

	env.padSetup();

	scene.setup();


	gl::enableDepthRead();
	gl::enableDepthWrite();

	gl::enable(GL_CULL_FACE);

#if 0
	// FOG�@�\��L���ɂ���
	gl::enable(GL_FOG);
	// ���[�h: GL_LINEAR�AGL_EXP�AGL_EXP2�̂����ꂩ
	glFogi(GL_FOG_MODE, GL_LINEAR);

	// GL_EXP�AGL_EXP2�Ŏg�����x�W��
	glFogf(GL_FOG_DENSITY, 1.0f);

	glFogf(GL_FOG_START, 500.0f);
	glFogf(GL_FOG_END, 1000.0f);
	GLfloat fog_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glFogfv(GL_FOG_COLOR, fog_color);
#endif
}

void DesignApp::shutdown()
{
	env.padShutDown();
	scene.shutdown();
}

void DesignApp::prepareSettings(Settings* settings)
{
	settings->setWindowSize(Vec2i(WIDTH, HEIGHT));
}

void DesignApp::update()
{
	timer.start(true);
	if (timer.getIsStop() == false)
	{
		env.padUpdate();
		env.padProcessEvent();
		scene.update();
		scene.shift();
	}

	timer.end();
}

void DesignApp::draw()
{
	gl::clear(Color(0, 0, 0));
	scene.draw();

#if _DEBUG
	timer.draw();
#endif
	c_Easing::update();

}



CINDER_APP_NATIVE(DesignApp, RendererGl)
