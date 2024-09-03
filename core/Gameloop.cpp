# include "Gameloop.hpp"


/* ____ CONSTRUCTORS ____ */
Gameloop::Gameloop(int width, int height)
	: FPS(120), frameDelay(1000 / FPS), width(width), height(height), game (width, height, &_audio) {
	plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
	plugin->update_speed(game.getLevelSpeed());
	activity = ON_GAME;
	direction = Down;

	loop();
}

Gameloop::Gameloop(const Gameloop &other)
	: FPS(other.FPS), frameDelay(other.frameDelay), width(other.width), height(other.height), game (other.game), _audio(other._audio) {
	plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
	plugin->update_speed(game.getLevelSpeed());
	activity = ON_GAME;
	direction = Down;

	loop();
}


/* ____ METHODS ____ */
void Gameloop::display() {
	plugin->update_snake(game.getSnakePositions(), game.getSnakeDirection());

	for (auto pos : game.getFoodPositions())
		plugin->update_food(pos);

	plugin->update_score(game.getScore());
	plugin->update_bestscore(game.getBestScore());
	if (game.over())
		activity = ON_GAME_OVER;
	plugin->display(activity);
}

inline Event Gameloop::loop_event() {
	Event event = plugin->poll_event(activity);
	switch (event) {
		case RIGHT:
			direction = Right;
			break;
		case LEFT:
			direction = Left;
			break;
		case UP:
			direction = Up;
			break;
		case DOWN:
			direction = Down;
			break;
		case ENTER:
			if (!game.over())
				break;
			game = game.newGame();
			event = DOWN;
			direction = Down;
			activity = ON_GAME;
			break;
		case CLICK_1P:
			if (!game.over())
				break;
			game = game.newGame();
			event = DOWN;
			direction = Down;
			activity = ON_GAME;
			break;
		case SPEED_UP:
			game.increaseSpeed();
			plugin->update_speed(game.getLevelSpeed());
			break;
		case SPEED_DOWN:
			game.decreaseSpeed();
			plugin->update_speed(game.getLevelSpeed());
			break;
		case F1:
			if (lib == SFML)
				break;
			lib = SFML;
			plugin.reset();
			plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
			break;
		case F2:
			if (lib == RAYLIB)
				break;
			lib = RAYLIB;
			plugin.reset();
			plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
			break;
		case F3:
			if (lib == SDL)
				break;
			lib = SDL;
			plugin.reset();
			plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
			break;
		default:
			break;
	}
	return event;
}

void Gameloop::clear () {
	plugin->clear();
}

void Gameloop::loop() {
	Event event = NONE;

	while (event != CLOSE) {
		frame_timer.reset();

		/* Event Handling */
		event = loop_event();

		if (frameDelay > frame_timer.elapsed()) {
			long int time_delay = frameDelay - frame_timer.elapsed();

			std::this_thread::sleep_for(std::chrono::milliseconds(time_delay));
		}

		clear();
		/* Move Snakes */
		if (!game.over() && timer.elapsed() > game.getSpeed()) {
			game.moveSnake(direction);
			timer.reset();
		}

		display();
	}
}



/* ____ COPLIEN ____ */
Gameloop::~Gameloop(){}

Gameloop	&Gameloop::operator=(const Gameloop &rhs) {
	if (this == &rhs)
		return *this;
	game = rhs.game;
	_audio = rhs._audio;
	plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
	plugin->update_speed(game.getLevelSpeed());
	activity = ON_GAME;
	direction = Down;

	return *this;
}
