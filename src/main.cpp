#include <blah.h>
#if WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#endif
using namespace Blah;

Batch batch;
TextureRef tex;

void getScreenResolution(int& width, int& height) {
	#if WIN32
		width = (int)GetSystemMetrics(SM_CXSCREEN);
		height = (int)GetSystemMetrics(SM_CYSCREEN);
	#else
		Display* disp = XOpenDisplay(NULL);
		Screen* scrn = DefaultScreenOfDisplay(disp);
		width = scrn->width;
		height = scrn->height;
	#endif
}

void startup()
{
	App::fullscreen(true);
	tex = Texture::create("../../../data/img/1.png");
}

void render()
{
	App::backbuffer->clear(Color::black);

	auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, Vec2::one, 0);
	batch.push_matrix(transform);

	batch.push_matrix(transform);
	batch.rect(Rect(-32, -32, 64, 64), Color::red);
	batch.tex(tex, Vec2(0, 0), Color::white);
	batch.pop_matrix();

	batch.render();
	batch.clear();
}

void update()
{

}

void shutdownwindow()
{

}

int main()
{
	int width, height;
	getScreenResolution(width, height);

	Config config;
	config.name = "Deusto Chess";
	config.width = width;
	config.height = height;
	config.target_framerate = 60;
	config.on_startup = startup;
	config.on_render = render;
	config.on_update = update;
	config.on_shutdown = shutdownwindow;

	App::run(&config);
	return 0;
}