# include "Menu.hpp"

Menu::Menu() {}

Menu::Menu(int width, int height) {
	this->init_game_over(width, height);
	this->init_menu(width, height);
	_last_click.reset();
}


Menu::~Menu() {

}

Menu::Menu(const Menu &other) {
	*this = other;
}

Menu	&Menu::operator=(const Menu &rhs) {
	if (this == &rhs)
		return *this;
	_buttons = rhs._buttons;
	return *this;
}

void	Menu::init_game_over(int width, int height) {
	std::pair<Activity, std::vector<Button>>	new_pair;
	sf::Rect<float>	r_button = sf::Rect<float>({0.5f * width, 0, 125, 60});
	Button		b;

	if ((height - 160) * 0.5 + 385 > height - 40)
		// (height - 160) * 0.5 + shift.y + card.y / 2 - shift_to_card - button.w
		r_button.top = (height - 160) * 0.5 + 238;
	else
		// (height - 160) * 0.5 + shift.y + card.y / 2 + shift_to_card;
		r_button.top = (height - 160) * 0.5 + 325;

	// Set Button Activty
	new_pair.first = ON_GAME_OVER;

	b.setTxt("Try Again");
	b.setTxtSize(25);
	b.setRect(r_button.left - 135, r_button.top, r_button.width, r_button.height);
	b.setOffSet(17, 13);
	b.setBgColor(sf::Color(0x4dc1f9ff));
	b.setTxtColor(sf::Color::White);
	b.setClickEvent(ON_GAME);
	new_pair.second.push_back(b);

	b.setTxt("Menu");
	b.setRect(r_button.left + 135 - 125, r_button.top, r_button.width, r_button.height);
	b.setOffSet(34, 13);
	b.setBgColor(sf::Color(0x4dc1f9ff));
	b.setTxtColor(sf::Color::White);
	b.setClickEvent(Activity::ON_MENU);
	new_pair.second.push_back(b);

	_buttons.insert(new_pair);
}

void	Menu::init_menu(int width, int height) {
	std::pair<Activity, std::vector<Button>>	new_pair;
	sf::Vector2f		beg = {0.2f * width, 0.3f * height};
	Button		b;
	sf::Color	menu_color(0x4DC1F9FF);

	// Set Button Activty
	new_pair.first = ON_MENU;

	b.setRect(0, 0, width, height);
	b.setBgColor(sf::Color::Black);
	b.setRounded(false);
	new_pair.second.push_back(b);

	b.setTxt("SupraSnake");
	b.setTxtColor(menu_color);
	b.setTxtSize(0.11 * std::min(height, width));
	b.setRect(beg.x, beg.y, width * 3 / 5, 0.1 * height);
	b.setOffSet(width * 0.05, 0);
	b.setRounded(true);
	new_pair.second.push_back(b);

	b.reset();

	b.setTxt("Play");
	b.setTxtColor(sf::Color::Black);
	b.setTxtSize(0.08 * std::min(height, width));
	b.setRect(beg.x, 0.6 * height, width * 3 / 5, 0.12 * height);
	b.setBgColor(menu_color);
	b.setClickEvent(Activity::ON_GAME);
	b.setOffSet(width * 0.23, height * 0.01);
	b.setRounded(true);
	new_pair.second.push_back(b);

	_buttons.insert(new_pair);
}


Activity	Menu::checkCollision(Activity act, float x, float y) {
	auto	it_map = _buttons.find(act);

	/* Avoid click interpretation on activity change */
	if (_last_click.elapsed() < 0.1)
		return ON_NONE;
	/* No buttons for activity */
	else if(it_map == _buttons.end())
		return ON_NONE;

	_last_click.reset();
	for (auto it = it_map->second.begin(); it != it_map->second.end(); it++)
		if (it->getRect().contains({x, y}))
			if (it->getEvent() != ON_NONE)
				return it->getEvent();

	return ON_NONE;
}

void	Menu::draw(const Activity &act, sf::RenderTarget &win){
	auto	it_map = _buttons.find(act);

	if (it_map == _buttons.end())
		return ;

	// Draw all butons
	for (auto it = it_map->second.begin(); it != it_map->second.end(); it++)
		it->draw(win);
}
