SFML	=	lib_nibbler_sfml.so
NAME	=	nibbler

$(NAME): core/main.cpp
	clang++ core/*.cpp -o $(NAME)

$(SFML): sfml/main.cpp
	clang++ sfml/*.cpp --shared -fPIC -o $(SFML) -lsfml-graphics -lsfml-window -lsfml-system

run: $(NAME) $(SFML)
	./nibbler


run2: $(NAME) $(SFML)
	valgrind ./nibbler
