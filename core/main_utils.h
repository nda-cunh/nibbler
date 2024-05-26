#ifndef MAIN_UTILS_HPP
# define MAIN_UTILS_HPP
#include <iostream>
#include <string>
#include <array>
#include <map>
#include <unistd.h>
#include <time.h>
#include "Plugin.hpp"
#include "Game.hpp"
#include "../include/utils.hpp"

#define CLOCK_FRAME	100000 
#define ERROR(msg)	std::cerr<<"\033[91;1mERROR \033[0;91m"<<msg<<".\033[m"<<std::endl

enum LIBS {
	SFML,
	RAYLIB,
	SDL,
	SFML_BIS
};

void	main_plugin_loop(int width, int height);

#endif
