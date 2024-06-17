#ifndef _GAMEOVER_HPP_
#define _GAMEOVER_HPP_

#include "RenderTexture.hpp"
#include "Text.hpp"

class Gameover : public RenderTexture {
	public:

		Gameover () : RenderTexture() {
			RenderTexture::create("./sdl/snake_sdl.bmp");
			score = 0;
			best_score = 0;
		}

		void create (int width, int height) {
			text.set_text(std::to_string(0));
			x_gameover = (- (this->get_width()/2.0) + width/2.0);
			y_gameover = (- (this->get_height()/2.0) + height/2.0);
		}

		void update_score (int score, int best_score) {
			this->score = score;
			this->best_score = best_score;
		}

		void draw (SDL_Renderer* renderer, int score, int best_score) {
			RenderTexture::draw (renderer, x_gameover, y_gameover);
			text.set_text(std::to_string(score));
			text.draw(renderer, x_gameover + 64, y_gameover + 120);
			text.set_text(std::to_string(best_score));
			text.draw(renderer, x_gameover + 208, y_gameover + 120);
		}

		void get_position (int &x, int &y) {
			x = this->x_gameover;
			y = this->y_gameover;
		}


	private:
		int x_gameover;
		int y_gameover;
		int score;
		int best_score ;
		Text text;

};

#endif
