#include "./main_utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <glib-2.0/glib.h>

int check_args_params(int ac, char **av, int &w, int &h, int &s) {
	GOptionContext *context;
	GError *error = NULL;

	int width = 0;
	int height = 0;
	int speed = 2;

	GOptionEntry entries[] = {
		{ "width", 'w', 0, G_OPTION_ARG_INT, &width, "width of window", "(10-20)" },
		{ "height", 'h', 0, G_OPTION_ARG_INT, &height, "height of window", "(10-20)" },
		{ "speed", 's', 0, G_OPTION_ARG_INT, &speed, "speed of window", "(1-5)" },
		{ NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL, NULL}
	};

	context = g_option_context_new("-  Nibbler -");
	g_option_context_set_summary(context, "Nibbler is a simple snake game.");
	g_option_context_add_main_entries(context, entries, NULL);
	g_option_context_parse(context, &ac, &av, &error);
	g_option_context_free(context);

	if (error != NULL) {
		ERROR(error->message);
		g_error_free(error);
		return false;
	} else if (width * height == 0) {
		ERROR("Width and Height must be set");
		return false;
	} else if (width < 10 || width > 20 || height < 10 || height > 20) {
		ERROR("Width and Height must be between 10 and 20");
		return false;
	} else if (speed < 1 || speed > 5) {
		ERROR("Speed must be between 1 and 5");
		return false;
	}

	w = width;
	h = height;
	s = speed;
	return true;
}

inline bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}


bool	check_args(int ac, char **av, int &w, int &h, int &s) {
	if (ac == 3 && is_number(av[1]) && is_number(av[2])) {
		int	width = std::stoi(av[1]);
		int	height = std::stoi(av[2]);

		if (width < 10 || height < 10)
			ERROR("Integers must be greater than 10");
		else if (width > 21 || height > 21)
			ERROR("Integers must be lower than 21");
		else {
			w = width;
			h = height;
			s = 2;
			return true;
		}
	} else
		return check_args_params(ac, av, w, h, s);
	return false;
}

int	main(int argc, char **argv)
{
	try {
		/* Check Arguments */
		int width, height, speed;
		if (!check_args(argc, argv, width, height, speed))
			return -1;

		std::cout << "\033[1;32m <===\033[92m Game Launched \033[32m==O-<\033[m" << std::endl;
		std::cout << "width:" << width << " height:" << height << " speed:" << speed << std::endl;
		main_plugin_loop(width, height);
	} catch (std::exception &e) {
		std::cerr << "Error runtime (" << e.what() << ")" << std::endl;
	}

	return (0);
}
