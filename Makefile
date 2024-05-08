SFML	=	lib_nibbler_sfml.so
NAME	=	nibbler
CFLAGS	=	-Wall -Wextra 
$(NAME): core/main.cpp
	clang++ $(CFLAGS) core/*.cpp -o $(NAME)

$(SFML): sfml/main.cpp
	clang++ $(CFLAGS) sfml/*.cpp --shared -fPIC -o $(SFML) -lsfml-graphics -lsfml-window -lsfml-system

run: $(NAME) $(SFML)
	./nibbler


run2: $(NAME) $(SFML)
	valgrind ./nibbler
