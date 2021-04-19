#include <blah.h>
using namespace Blah;

Batch batch;
//TextureRef tex;

void startup()
{
	//tex = Texture::create("player.png");
}

void render()
{
	App::backbuffer->clear(Color::black);

	auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, Vec2::one, 0);
	batch.push_matrix(transform);

	batch.push_matrix(transform);
	batch.rect(Rect(-32, -32, 64, 64), Color::red);
	//batch.tex(tex, Vec2(64, 0), Color::white);
	batch.pop_matrix();

	batch.render();
	batch.clear();
}

void update()
{

}

void shutdown()
{

}

int main()
{
	Config config;
	config.name = "Deusto Chess";
	config.width = 1280;
	config.height = 720;
	config.target_framerate = 60;
	config.on_startup = startup;
	config.on_render = render;
	config.on_update = update;
	config.on_shutdown = shutdown;

	App::run(&config);
	return 0;
}