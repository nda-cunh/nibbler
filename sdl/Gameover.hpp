#ifndef _GAMEOVER_HPP_
#define _GAMEOVER_HPP_

#include "RenderTexture.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "../include/IPlugin.hpp"

class Gameover : public RenderTexture {
	public:
		Gameover ();
		~Gameover ();
		void createGameOver (int width, int height);
		void update_score (int score);
		void update_bestscore (int best_score);
		void draw (SDL_Renderer* renderer, int px = 0, int py = 0) override;
		void get_position (int &x, int &y);
		void onHover (int px, int py);
		Event onClick (int px, int py);

	private:
		int x_gameover;
		int y_gameover;
		int score;
		int best_score ;
		Text text;
		std::shared_ptr<Button> button_retry;
		std::shared_ptr<Button> button_menu;

};

#endif
