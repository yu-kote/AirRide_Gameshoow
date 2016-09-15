#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder/gl/Light.h"        // ライティング
#include "cinder/gl/Material.h"     // マテリアル(材質)

#include "Share/Share.h"
#include "Share/FrameTimer.h"
#include "Input/InputEvent.h"
#include "Scene/SceneManager/SceneManager.h"
#include "Share/Easing/Easing.h"
#include "Share/Interface/Interface.h"
#include "Share/Time.h"
#include "TaskManager/TextureManager.h"
#include "TaskManager/SoundManager.h"
#include "TaskManager/ObjDataManager.h"
#include "Share/Resize.h"


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

	void resize()override;
private:

	SceneManager scene;

	FrameTimer timer;
	CameraPersp camera;

	bool is_fullscreen;
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
	is_fullscreen = true;
	setFullScreen(is_fullscreen);
	LEAPHANDS.Setup();
	TextureGet.setup();
	SoundGet.setup();
	ObjDataGet.setup();

	Interface::single();
	env.padSetup();

	scene.setup();


	gl::enableDepthRead();
	gl::enableDepthWrite();

	gl::enable(GL_CULL_FACE);

#if 0
	// FOG機能を有効にする
	gl::enable(GL_FOG);
	// モード: GL_LINEAR、GL_EXP、GL_EXP2のいずれか
	glFogi(GL_FOG_MODE, GL_LINEAR);

	// GL_EXP、GL_EXP2で使う密度係数
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

void DesignApp::resize()
{
	ResizeGet.resize();
}

void DesignApp::prepareSettings(Settings* settings)
{
	settings->setWindowSize(Vec2i(WIDTH, HEIGHT));
}

void DesignApp::update()
{
	if (env.isPush(KeyEvent::KEY_1))
	{
		is_fullscreen = !is_fullscreen;
		setFullScreen(is_fullscreen);
	}
	timer.start(true);
	if (timer.getIsStop() == false)
	{
		TIME.update(static_cast<float>(getElapsedSeconds()), static_cast<int>(getElapsedFrames()));
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
	//Params->draw();
}



CINDER_APP_NATIVE(DesignApp, RendererGl)
