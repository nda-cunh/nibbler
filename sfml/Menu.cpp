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
	Button		b;

	// Set Button Activty
	new_pair.first = ON_GAME_OVER;

	b.setTxt("LOL");
	b.setRect(0, 0, 200, 100);
	b.setBgColor(sf::Color::Green);
	// b.setTxtColor(sf::Color::Magenta);
	// b.centerText();
	new_pair.second.push_back(b);


	_buttons.insert(new_pair);
}

void	Menu::init_menu(int width, int height) {
	std::pair<Activity, std::vector<Button>>	new_pair;
	Button		b;

	// Set Button Activty
	new_pair.first = ON_MENU;

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
