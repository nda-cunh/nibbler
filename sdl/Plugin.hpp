#include <memory>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <cairo/cairo.h>
#include "Text.hpp"
#include "RenderTexture.hpp"
#include "../include/IPlugin.hpp"
#include "Damier.hpp"
#include "Button.hpp"
#include "Gameover.hpp"

class Plugin : public IPlugin {
	public:
		Plugin ();
		Plugin(const Plugin &p);
		Plugin	&operator=(const Plugin &p);
		virtual ~Plugin();

		void open (int x, int y) override;
		void close () override;
		Event poll_event (Activity) override;
		void update_snake (const std::deque<Position> &queue) override;
		void update_food (Position &position) override;
		void update_score (int score) override;
		void update_bestscore (int score) override;
		void clear () override;
		void display (Activity activity) override;

	private:
		SDL_Window* win;
		SDL_Renderer* renderer;

		Damier damier;

		Gameover gameover;
		RenderTexture render_game;

		Text text_score;
		Text text_bestscore;

		const int tile_size = 32;
		int width;
		int height;
		int x;
		int y;
};

