# include "Menu.hpp"

Menu::Menu() {}

Menu::Menu(int width, int height) {
	std::pair<Activity, std::vector<Button>>	new_pair;
	new_pair.first = ON_GAME_OVER;
	this->init_game_over(width, height);
	this->init_menu(width, height);
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
	_current_activity = rhs._current_activity;
	return *this;
}

void	Menu::init_game_over(int width, int height) {
	std::pair<Activity, std::vector<Button>>	new_pair;
	new_pair.first = ON_GAME_OVER;
	Vector2		beg = {0.2f * width, 0.4f * height};
	Button		b;

	b.setBgColor(GetColor(0x00000084));
	b.setRect(0, 0, width, height);
	b.setTxt("");
	new_pair.second.push_back(b);
	b.reset();

	b.setTxt("Game Over");
	b.setTxtSize(0.07 * std::min(height, width));
	b.setRect(beg.x, beg.y,
		width - 2.f * beg.x, height - 2.f * beg.y);
	b.centerText();
	new_pair.second.push_back(b);
	b.reset();
	
	Vector2	size = {(width - 2.f * beg.x) / 2.1f, TILE_SIZE};

	b.setTxt("Try Again");
	b.setTxtSize(20);
	b.setRect(beg.x, height - 0.8f * beg.y,
		size.x, size.y);
	b.centerText();
	b.setClickEvent(Activity::ON_GAME);
	new_pair.second.push_back(b);

	b.setTxt("Menu");
	b.setRect(width - beg.x - size.x, height - 0.8f * beg.y,
		size.x, size.y);
	b.centerText();
	b.setClickEvent(Activity::ON_MENU);
	new_pair.second.push_back(b);
	b.reset();

	_buttons.insert(new_pair);
}

void	Menu::init_menu(int width, int height) {
	std::pair<Activity, std::vector<Button>>	new_pair;
	new_pair.first = ON_MENU;
	Vector2		beg = {0.2f * width, 0.4f * height};
	Button		b;

	b.setBgColor(GetColor(0x003300FF));
	b.setRect(0, 0, width, height);
	new_pair.second.push_back(b);

	b.setTxt("SupraSnake");
	b.setTxtColor(GetColor(0x12CC12FF));
	b.setRect(beg.x, beg.y, width * 3 / 5, 0.12 * height);
	b.setTxtSize(0.07 * std::min(height, width));
	b.centerText();
	new_pair.second.push_back(b);

	b.setTxt("Play");
	b.setTxtColor(GetColor(0x12CC12FF));
	b.setBgColor(GetColor(0x005500AA));
	b.setRect(beg.x, 0.6 * height, width * 3 / 5, 0.12 * height);
	b.setTxtSize(0.04 * std::min(height, width));
	b.centerText();
	b.setClickEvent(Activity::ON_GAME);
	new_pair.second.push_back(b);

	_buttons.insert(new_pair);
}


Activity	Menu::checkCollision(Activity act, float x, float y) {
	auto	it_map = _buttons.find(act);
	if (it_map == _buttons.end())
		return ON_NONE;

	for (auto it = it_map->second.begin(); it != it_map->second.end(); it++) {
		if (CheckCollisionPointRec({x, y}, it->getRect()) && it->getEvent() != ON_NONE) {
			return it->getEvent();
		}
	}

	return ON_NONE;
}

void	Menu::draw(const Activity &act) {
	if (act == ON_GAME)
		return;

	auto	it_map = _buttons.find(act);
	if (it_map == _buttons.end())
		return ;
	for (auto it = it_map->second.begin(); it != it_map->second.end(); it++)
		it->draw();
}
