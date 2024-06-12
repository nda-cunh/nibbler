# include "Menu.hpp"

/* ____ CONSTRUCTOR & COPLIEN ____ */
Menu::Menu() : TILE_SIZE(32) {}

Menu::Menu(const Menu &other): TILE_SIZE(other.TILE_SIZE) {
	*this = other;
}

Menu::Menu(int width, int height, int tile_size): TILE_SIZE(tile_size) {
	this->init_game_over(width, height);
	this->init_menu(width, height);
	_last_click.reset();
}

Menu::~Menu() {}

Menu	&Menu::operator=(const Menu &rhs) {
	if (this == &rhs)
		return *this;
	_buttons = rhs._buttons;
	_last_click = rhs._last_click;
	return *this;
}


/* ____ INIT ACTIVITIES ____ */

void	Menu::init_game_over(int width, int height) {
	std::pair<Activity, std::vector<Button>>	new_pair;
	Vector2		beg = {0.2f * width, 0.4f * height};

	// Set Button Activty
	new_pair.first = ON_GAME_OVER;

	// Darker background
	{
		Button		b;

		b.setBgColor(GetColor(0x00000084));
		b.setRect(0, 0, width, height);
		new_pair.second.push_back(b);
	}

	{
		Button		b;

		b.setTxt("Game Over");
		b.setTxtColor(WHITE);
		b.setBgColor(GetColor(0x578a34ff));
		b.setTxtSize(0.07 * std::min(height, width));
		b.setRect(beg.x, beg.y,
				width - 2.f * beg.x, height - 2.f * beg.y);
		b.centerText();
		new_pair.second.push_back(b);
	}

	{
		Button	b;
		Vector2	size = {(width - 2.f * beg.x) / 2.1f, TILE_SIZE * 1.2f};


		b.setTxt("Try Again");
		b.setTxtSize(20);
		b.setTxtColor(WHITE);
		b.setBgColor(GetColor(0x578a34ff));
		b.setClickEvent(Activity::ON_GAME);
		b.setRect(beg.x, height - 0.8f * beg.y,
				size.x, size.y);
		b.centerText();
		new_pair.second.push_back(b);

		b.setTxt("Menu");
		b.setClickEvent(Activity::ON_MENU);
		b.setRect(width - beg.x - size.x, height - 0.8f * beg.y,
				size.x, size.y);
		b.centerText();
		new_pair.second.push_back(b);
	}

	_buttons.insert(new_pair);
}

void	Menu::init_menu(int width, int height) {
	std::pair<Activity, std::vector<Button>>	new_pair;
	Vector2		beg = {0.2f * width, 0.3f * height};

	// Set Button Activty
	new_pair.first = ON_MENU;

	{
		Button		b;

		b.setRect(0, 0, width, height);
		b.setBgColor(BLACK);
		new_pair.second.push_back(b);
	}

	{
		Button		b;

		b.setTxt("SupraSnake");
		b.setTxtColor(GetColor(0x12CC12FF));
		b.setTxtSize(0.11 * std::min(height, width));
		b.setRect(beg.x, beg.y, width * 3 / 5, 0.12 * height);
		b.setBgColor(BLACK);
		b.centerText();
		new_pair.second.push_back(b);
	}

	{
		Button		b;

		b.setTxt("Play");
		b.setTxtColor(BLACK);
		b.setTxtSize(0.08 * std::min(height, width));
		b.setRect(beg.x, 0.6 * height, width * 3 / 5, 0.12 * height);
		b.setBgColor(GetColor(0x12CC12FF));
		b.setClickEvent(Activity::ON_GAME);
		b.centerText();
		new_pair.second.push_back(b);
	}

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
		if (CheckCollisionPointRec({x, y}, it->getRect()))
			if (it->getEvent() != ON_NONE)
				return it->getEvent();

	return ON_NONE;
}

void	Menu::draw(const Activity &act) {
	auto	it_map = _buttons.find(act);

	if (it_map == _buttons.end())
		return ;

	// Draw all butons
	auto	v_buttons = it_map->second;
	for (auto it = v_buttons.begin(); it != v_buttons.end(); it++)
		it->draw();
}
