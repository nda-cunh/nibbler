#ifndef _GAMEOVER_HPP_
#define _GAMEOVER_HPP_

#include "RenderTexture.hpp"
#include "Button.hpp"
#include "Text.hpp"

class Gameover : public RenderTexture {
	public:
		Gameover ();
		Gameover(const Gameover &g);
		Gameover &operator= (const Gameover &g);
		~Gameover ();
		void createGameOver (int width, int height, int tile_y);
		void update_score (int score);
		void update_bestscore (int best_score);
		void draw (SDL_Renderer* renderer, int px = 0, int py = 0) override;
		void get_position (int &x, int &y);
		void hover (int x, int y);
		int collide(int x, int y);

	private:
		int x_gameover;
		int y_gameover;
		int score;
		int best_score ;
		Text text;
		std::shared_ptr<Button> button_retry;
		std::shared_ptr<Button> button_quit;

};

#endif
