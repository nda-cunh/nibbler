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
		/* ---- Constructors ---- */
		Gameloop(int width, int height, int speed);
		Gameloop(const Gameloop &other);
		/* ---- Coplien  ---- */
		Gameloop &operator=(const Gameloop &rhs);
		~Gameloop();

		/* ---- Methods ---- */
		inline Event loop_event();
		void display() ;
		void clear ();
		void loop();



	private:
		const std::map<LIBS, std::string> lib_names = {
			{SFML,            "./libsfml.so"},
			{SDL,             "./libsdl.so"},
			{RAYLIB,          "./libraylib.so"}
		};
		const int	FPS;
		const int	frameDelay;
		const float	speedRate;
		const int	width;
		const int	height;

		std::unique_ptr<Plugin> plugin;
		Game			game;
		ModuleAudio		_audio;
		Activity		activity;
		LIBS			lib = SFML;
		Direction		direction;
		Timer			timer;
		Timer			frame_timer;
};

#endif
