#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include "./main_utils.h"
#include "Timer.hpp"
#include <memory>
#include <deque>
#include <stack>
#include <thread>
#include <iostream>


class Gameloop
{
	public:
		Gameloop(int width, int height) : FPS(120), frameDelay(1000 / FPS), width(width), height(height), game (width, height, &_audio, ON_MENU) {
			plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
			plugin->update_speed(game.getLevelSpeed());
			activity = ON_MENU;
			last_gamemode = ON_GAME_1P;
			dir_p1 = Down;
			dir_p2 = Down;
			loop();
		}

		void display() {
			if (activity != Activity::ON_MENU) {
				if (activity == ON_GAME_1P) {
					plugin->update_snake(game.getSnakePositions());
					plugin->update_score(game.getScore());
					plugin->update_bestscore(game.getBestScore());
				} else {
					plugin->update_snake(game.getSnakePositions(0), game.getSnakePositions(1));
					plugin->update_score(game.getScore(0), game.getScore(1));
					plugin->update_bestscore(game.getBestScore(0), game.getBestScore(1));
				}

				for (auto pos : game.getFoodPositions())
					plugin->update_food(pos);

				if (game.over())
					activity = ON_GAME_OVER;
			} else
				plugin->update_speed(game.getLevelSpeed());
			plugin->display(activity);
		}

		inline Event loop_event() {
			Event event = plugin->poll_event(activity);
			switch (event) {
				case RIGHT:
					dir_p1 = Right;
					break;
				case LEFT:
					dir_p1 = Left;
					break;
				case UP:
					dir_p1 = Up;
					break;
				case DOWN:
					dir_p1 = Down;
					break;
				case W_UP:
					dir_p2 = Up;
					break;
				case A_LEFT:
					dir_p2 = Left;
					break;
				case S_DOWN:
					dir_p2 = Down;
					break;
				case D_RIGHT:
					dir_p2 = Right;
					break;
				case ENTER:
					if (!game.over())
						break;
					game = game.newGame(last_gamemode);
					event = DOWN;
					dir_p1 = Down;
					dir_p2 = Down;
					activity = last_gamemode;
					break;
				case CLICK_1P:
					if (!game.over())
						break;
					game = game.newGame(ON_GAME_1P);
					event = DOWN;
					dir_p1 = Down;
					activity = ON_GAME_1P;
					last_gamemode = ON_GAME_1P;
					break;
				case CLICK_2P:
					if (!game.over())
						break;
					game = game.newGame(ON_GAME_2P);
					event = DOWN;
					dir_p1 = Down;
					dir_p2 = Down;
					activity = ON_GAME_2P;
					last_gamemode = ON_GAME_2P;
					break;
				case CLICK_MENU:
					activity = ON_MENU;
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
			return event;
		}

		void clear () {
			plugin->clear();
		}

		void loop() {
			Event event = NONE;

			while (event != CLOSE) {
				frame_timer.reset();

				/* Event Handling */
				event = loop_event();

				if (frameDelay > frame_timer.elapsed()) {
					long int time_delay = frameDelay - frame_timer.elapsed();

					std::this_thread::sleep_for(std::chrono::milliseconds(time_delay));
				}

				clear();
				/* Move Snakes */
				if (!game.over() && timer.elapsed() > game.getSpeed()) {
					game.moveSnake(dir_p1);
					if (activity == ON_GAME_2P)
						game.moveSnake(dir_p2, 1);
					timer.reset();
				}

				display();
			}
		}

		~Gameloop()  {

		}


	private:
		const std::map<LIBS, std::string> lib_names = {
			{SFML,            "./libsfml.so"},
			{SFML_BIS,        "./libsfml_bis.so"},
			{SDL,             "./libsdl.so"},
			{RAYLIB,          "./libraylib.so"}
		};
		const int	FPS;
		const int	frameDelay;
		const int	width;
		const int	height;

		std::unique_ptr<Plugin> plugin;
		Game			game;
		ModuleAudio		_audio;
		Activity		activity;
		Activity		last_gamemode;
		LIBS			lib = SDL;
		Direction		dir_p1;
		Direction		dir_p2;
		Timer			timer;
		Timer			frame_timer;
};

#endif
