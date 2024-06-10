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
	const Position	card_over = {324, 389};
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
	Button		b;

	// Set Button Activty
	new_pair.first = ON_MENU;

	b.setTxt("SNAKE");
	b.setTxtSize(84);
	b.setTxtColor(sf::Color(0x4df9c1ff));
	b.setOffSet(0.35 * width, 0.3 * height);
	b.setRect(0, 0, width, height);
	b.setBgColor(sf::Color::Black);
	new_pair.second.push_back(b);

	b.setTxt("Play 1P");
	b.setRect(0.25 * width, 0.5 * height, 0.5 * width, 50);
	b.setTxtSize(42);
	b.setBgColor(sf::Color(0x4df9c1ff));
	b.setOffSet(0.18 * width, 0);
	b.setTxtColor(sf::Color::Black);
	b.setClickEvent(Activity::ON_GAME);
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
