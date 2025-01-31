#include "Plugin.hpp"

Plugin::Plugin () :
	win(NULL),
	renderer(NULL),
	damier(),
	menu(),
	gameover(),
	render_game(),
	text_score(),
	text_bestscore(),
	tile_size(32),
	width(0),
	height(0),
	x(0),
	y(0)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL_Init failed");
}

Plugin::~Plugin() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void Plugin::open (int x, int y) {
	SDL_DisplayMode dm;
	this->x = x;
	this->y = y;
	width = x * tile_size;
	height = y * tile_size;

	////////////////////////////////////////
	///	Window
	////////////////////////////////////////
	win = SDL_CreateWindow("Nibbler - SDL2", 0, 0, width + tile_size * 2, height + tile_size * 2 * 2, SDL_WINDOW_HIDDEN);
	if (win == NULL)
		throw std::runtime_error("SDL_CreateWindow failed" + std::string(SDL_GetError()));
	if (SDL_GetDesktopDisplayMode(0, &dm) < 0)
		throw std::runtime_error("SDL_GetDesktopDisplayMode failed" + std::string(SDL_GetError()));
	SDL_SetWindowPosition(win, (dm.w - width) / 2, (dm.h - height) / 2);
	SDL_ShowWindow(win);

	////////////////////////////////////////
	///	Renderer
	////////////////////////////////////////
	renderer = SDL_CreateRenderer(win, 0, 0);
	if (renderer == NULL)
		throw std::runtime_error("SDL_CreateRenderer failed");

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	////////////////////////////////////////
	///	Damier
	////////////////////////////////////////
	damier.create(width, height, tile_size, x, y);

	////////////////////////////////////////
	///	RenderTexture (Game)
	////////////////////////////////////////
	render_game.create(width, height);

	////////////////////////////////////////
	///	Menu
	////////////////////////////////////////

	int w;
	int h;
	SDL_GetWindowSize(win, &w, &h);

	menu.create(w, h);

	////////////////////////////////////////
	/// Gameover
	////////////////////////////////////////

	gameover.createGameOver(w, h);
}

void Plugin::close ()  {
}

static inline Event event_keydown(SDL_Scancode scancode) {
	switch (scancode) {
		case SDL_SCANCODE_LEFT:
			return LEFT;
		case SDL_SCANCODE_A:
			return A_LEFT;
		case SDL_SCANCODE_D:
			return D_RIGHT;
		case SDL_SCANCODE_W:
			return W_UP;
		case SDL_SCANCODE_S:
			return S_DOWN;
		case SDL_SCANCODE_RIGHT:
			return RIGHT;
		case SDL_SCANCODE_UP:
			return UP;
		case SDL_SCANCODE_DOWN:
			return DOWN;
		case SDL_SCANCODE_RETURN:
			return ENTER;
		case SDL_SCANCODE_ESCAPE:
			return CLOSE;
		case SDL_SCANCODE_F1:
			return F1;
		case SDL_SCANCODE_F2:
			return F2;
		case SDL_SCANCODE_F3:
			return F3;
		case SDL_SCANCODE_MINUS:
			return SPEED_DOWN;
		case SDL_SCANCODE_KP_PLUS:
			return SPEED_UP;
		default:
			return NONE;
	}
}

Event Plugin::poll_event (Activity)   {
	int px, py;
	SDL_Event event;
	Event e = NONE;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				e = CLOSE;
				break;

			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&px, &py);
				gameover.onHover(px, py);
				menu.collide_hover(px, py);
				break;


			case SDL_MOUSEBUTTONUP:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						Event res;
						SDL_GetMouseState(&px, &py);
						res = gameover.onClick(px, py);
						if (res != NONE)
							return res;
						res = menu.collide_click(px, py);
						if (res != NONE)
							return res;
						break;
					default:
						e = NONE;
						break;
				}

			case SDL_KEYDOWN:
				e = event_keydown(event.key.keysym.scancode);
				break;

			default:
				e = NONE;
				break;
		}
		if (e != NONE)
			return e;
	}
	return e;
}





/**
 * Update the snake on the screen
 */
void Plugin::update_snake (const std::deque<Position> &snake1, const std::deque<Position>&snake2) { 
	SDL_Rect rect;

	rect = { 0, 0, tile_size, tile_size };

	for (const auto &pos : snake1) {
		rect.x = pos.x * tile_size,
			rect.y = pos.y * tile_size,
			render_game.draw_rect(&rect, 81, 128, 243);
	}
	rect.x = snake1[0].x * tile_size,
		rect.y = snake1[0].y * tile_size,
		render_game.draw_rect (&rect, 49, 94, 255);

	if (snake2.empty())
		return;

	for (const auto &pos : snake2) {
		rect.x = pos.x * tile_size,
			rect.y = pos.y * tile_size,
			render_game.draw_rect(&rect, 243, 196, 81);
	}
	rect.x = snake2[0].x * tile_size,
		rect.y = snake2[0].y * tile_size,
		render_game.draw_rect (&rect, 223, 176, 61);
}

/**
 * Update the food on the screen
 */
void Plugin::update_food (Position &position)  {
	SDL_Rect rect = {
		position.x * tile_size,
		position.y * tile_size,
		tile_size,
		tile_size
	};
	render_game.draw_rect (&rect, 255, 0, 0);
}

void Plugin::update_score (int score, int)  {
	SDL_Rect rect;

	rect = {tile_size, tile_size / 2, tile_size, tile_size};

	// draw the apple score (red sqaure)
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);

	// draw the text score
	text_score.set_text(std::to_string(score));
	text_score.draw(renderer, tile_size * 2.5 - text_score.get_width() / 2.0, tile_size * 1 - text_score.get_height() / 2.0);
	gameover.update_score(score);
}

void Plugin::update_bestscore (int score, int)  {
	SDL_Rect rect;

	rect = {190, tile_size / 2, tile_size, tile_size};

	// draw the best score (yellow sqaure)
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);

	// draw the text best score
	text_bestscore.set_text(std::to_string(score));
	text_bestscore.draw(renderer, tile_size * 7.5 - text_score.get_width() / 2.0, tile_size * 1 - text_score.get_height() / 2.0);
	gameover.update_bestscore(score);
}

void Plugin::update_speed (int speed)  {
	menu.update_speed(speed);
}


void Plugin::clear ()  {
	SDL_Rect rect = {0, 0, width + tile_size * 2, tile_size * 2};

	// Draw Wall
	SDL_SetRenderDrawColor(renderer, 87, 138, 52, 255);
	SDL_RenderClear(renderer);

	// Draw Menu
	SDL_SetRenderDrawColor(renderer, 74, 117, 44, 255);
	SDL_RenderFillRect(renderer, &rect);

	// Clear the game RenderTexture and draw the damier
	render_game.clear();
	render_game.draw(damier, 0, 0);
}

void Plugin::display (Activity activity)  {
	switch (activity) {
		case ON_MENU:
			menu.draw(renderer);
			break;

		case ON_GAME_OVER:
			render_game.draw (renderer, tile_size, tile_size*3);
			SDL_Rect rect;
			int w, h;
			SDL_GetWindowSize(win, &w, &h);
			rect = {0, 0, w, h};
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
			SDL_RenderFillRect(renderer, &rect);

			// Draw the gameover screen
			gameover.draw(renderer);
			break;

		default:
			render_game.draw (renderer, tile_size, tile_size*3);
			break;
	}

	// display all the render on the screen
	SDL_RenderPresent(renderer);
}
