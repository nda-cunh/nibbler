#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include "Text.hpp"
#include "RenderTexture.hpp"

class Button : public RenderTexture {
	public:
		Button () {
			RenderTexture::create(200, 200);
		}

		~Button () {

		}
		
		void create (int width, int height, std::string text) {
			this->width = width;
			this->height = height;
			RenderTexture::create(width, height);
			_text.set_text(text);
		}
	
		void init_draw() {
			this->clear();
		}

		void draw (SDL_Renderer *renderer, int x, int y) override {
			init_draw();
			RenderTexture::draw(renderer, x, y);
			//FIXME: draw text
			_text.draw (renderer, 1, 0);
		}

	private: 
		int width;
		int height;
		Text _text;
};

#endif
