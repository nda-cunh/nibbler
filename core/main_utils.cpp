#include "./main_utils.h"
#include "Timer.hpp"
#include <memory>
#include <deque>
#include <stack>
#include <thread>

// File: game_loop.cpp

// updateAndDisplayGameState(...)
static void display(const Game &game, Plugin &plugin, const Direction &dir, Activity &act) {
	plugin.clear();
	if (act != Activity::ON_MENU) {
		plugin.update_snake(game.getSnakePositions(), dir);

		for (auto pos : game.getFoodPositions())
			plugin.update_food(pos);

		plugin.update_score(game.getScore());
		plugin.update_bestscore(game.getBestScore());
		if (game.over())
			act = ON_GAME_OVER;
	}
	plugin.display(act);
}

// runGameLoop(...)
void	main_plugin_loop(int width, int height) {
	ModuleAudio				_audio;
	std::unique_ptr<Plugin> plugin;
	Game		game(width, height);
	game.setAudio(&_audio);
	Activity	current_act = ON_GAME;
	Event		event = DOWN;
	LIBS		lib = SFML;
	const auto	lib_names = std::map<LIBS, std::string>({
			{SFML, "./libsfml.so"},
			{SFML_BIS, "./libsfml_bis.so"},
			{SDL, "./libsdl.so"},
			{RAYLIB, "./libraylib.so"}
			});
	Direction	direction = Down;
	Timer		timer;
	

	const int	FPS = 120;
	const int	frameDelay = 1000 / FPS;
	Timer		frame_timer;

	plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
	plugin->update_speed(game.getLevelSpeed());

	while (event != CLOSE) {
		frame_timer.reset();

		/* Event Handling */
		event = plugin->poll_event(current_act);
		switch (event) {
			case RIGHT:
				direction = Right;
				_audio.playSound(IAudioModule::RIGHT);
				break;
			case LEFT:
				_audio.playSound(IAudioModule::LEFT);
				direction = Left;
				break;
			case UP:
				_audio.playSound(IAudioModule::UP);
				direction = Up;
				break;
			case DOWN:
				_audio.playSound(IAudioModule::DOWN);
				direction = Down;
				break;
			case ENTER:
				if (!game.over())
					break;
				game = game.newGame();
				game.setAudio(&_audio);
				event = DOWN;
				direction = Down;
				current_act = ON_GAME;
				break;
			case CLICK_1P:
				if (!game.over())
					break;
				game = game.newGame();
				game.setAudio(&_audio);
				event = DOWN;
				direction = Down;
				current_act = ON_GAME;
				break;
			case CLICK_MENU:
				current_act = ON_MENU;
				break;
			case SPEED_UP:
				game.increaseSpeed();
				plugin->update_speed(game.getLevelSpeed());
				break;
			case SPEED_DOWN:
				game.decreaseSpeed();
				plugin->update_speed(game.getLevelSpeed());
				break;
			case F1:
				if (lib == SFML)
					break;
				lib = SFML;
				plugin.reset();
				plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
				break;
			case F2:
				if (lib == RAYLIB)
					break;
				lib = RAYLIB;
				plugin.reset();
				plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
				break;
			case F3:
				if (lib == SDL)
					break;
				lib = SDL;
				plugin.reset();
				plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
				break;
			default:
				break;
		}

		if (frameDelay > frame_timer.elapsed()) {
			long int time_delay = frameDelay - frame_timer.elapsed();

			std::this_thread::sleep_for(std::chrono::milliseconds(time_delay));
		}

		/* Move Snakes */
		if (!game.over() && timer.elapsed() > game.getSpeed()) {
			game.moveSnake(direction);
			timer.reset();
		}

		display(game, *plugin, game.getSnakeDirection(), current_act);	
	}
}
