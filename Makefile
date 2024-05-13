NAME_SFML	= lib_nibbler_sfml.so
NAME_SFML2	= lib_nibbler_sfml_bis.so
NAME = nibbler
CFLAGS = -fPIC -Wall -Wextra -O3

############
#  SOURCE  #
############
CORE_SRCS = core/main.cpp core/main_utils.cpp core/Game.cpp core/Plugin.cpp
CORE_OBJS = $(CORE_SRCS:.cpp=.o) 
SFML_SRCS = sfml/main.cpp sfml/menu.cpp sfml/snake.cpp sfml/animation.cpp sfml/apple.cpp sfml/background.cpp
SFML_OBJS = $(SFML_SRCS:.cpp=.o) 
SFML2_SRCS = sfml_bis/main.cpp
SFML2_OBJS = $(SFML2_SRCS:.cpp=.o) 

############
#   CORE   #
############
all: $(NAME)

$(NAME): $(CORE_OBJS) $(NAME_SFML) $(NAME_SFML2)
	clang++ $(CORE_OBJS) -o $(NAME)

############
#   SFML   #
############
SFML_LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

$(NAME_SFML): $(SFML_OBJS)
	clang++ $(SFML_OBJS)  $(SFML_LDFLAGS) --shared -fPIC -o $(NAME_SFML) 

$(NAME_SFML2): $(SFML2_OBJS)
	clang++ $(SFML2_SRCS)  $(SFML_LDFLAGS) --shared -fPIC -o $(NAME_SFML2) 



###########
# UTILITY #
###########

%.o: %.cpp
	clang++ $(CFLAGS) $< -c -o $@

run: $(NAME) $(NAME_SFML) $(NAME_SFML2)
	./$(NAME) 8 20

run2: $(NAME) $(NAME_SFML) $(NAME_SFML2)
	valgrind ./$(NAME) 8 20

clean:
	rm -rf $(SFML_OBJS)
	rm -rf $(SFML2_OBJS)
	rm -rf $(CORE_OBJS)

fclean: clean
	rm -f $(NAME) $(NAME_SFML) $(NAME_SFML2)

re: fclean all
