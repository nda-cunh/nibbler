#include <iostream>
#include <string>
#include <dlfcn.h>
#include <unistd.h>

#include "../include/IGame.hpp"

class Game : public IGame {
	private:
		IGame* game;
		void* handler;
	public:
		~Game(){
			auto func = (IGame*(*)())dlsym(handler, "destroy_ptr");
			func();
			dlclose(handler);
		}
		Game (std::string so) {
			handler = dlopen(so.c_str(), RTLD_LAZY);
			auto func = (IGame*(*)())dlsym(handler, "get_ptr");
			game = func();
		}
		void open () {
			game->open();
		}
		void rect (int x, int y) {
			game->rect(x, y);
		}
		void close() {
			game->close();
		}
		void iteration() {
			game->iteration();
		}
};

int	main(int ac, char **av)
{
	Game game("lib_nibbler_sfml.so");
	game.open();
	for (int  i = 0; i < 500; i++) {
		game.rect(i, i);
		game.iteration();
		usleep(4000);
	}
	game.close();
	

	return (0);
}
