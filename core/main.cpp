#include "./main_utils.h"

inline bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


bool	check_args(int ac, char **av, int &w, int &h) {
	if (ac != 3)
		ERROR("Wrong args number");
	else if (!is_number(av[1]) || !is_number(av[2]))
		ERROR("Args must be integers");
	else {
		int	width = std::stoi(av[1]);
		int	height = std::stoi(av[2]);

		if (width < 10 || height < 10)
			ERROR("Integers must be greater than 10");
		else if (width > 42 || height > 42)
			ERROR("Integers must be lower than 42");
		else {
			w = width;
			h = height;
			return true;
		}
	}
	return false;
}

int	main(int argc, char **argv)
{
	/* Check Arguments */
	int width, height;
	if (!check_args(argc, argv, width, height))
		return -1;

	main_plugin_loop(width, height);

	return (0);
}
