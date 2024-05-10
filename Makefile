NAME_SFML = lib_nibbler_sfml.so
NAME = nibbler
CFLAGS = -Wall -Wextra -O3

############
#  SOURCE  #
############
CORE_SRCS = core/main.cpp 
CORE_OBJS = $(CORE_SRCS:.cpp=.o) 
SFML_SRCS = sfml/main.cpp sfml/snake.cpp sfml/animation.cpp sfml/apple.cpp sfml/background.cpp
SFML_OBJS = $(SFML_SRCS:.cpp=.o) 

############
#   CORE   #
############
all: $(NAME)

$(NAME): $(CORE_OBJS) $(NAME_SFML)
	clang++ $(CORE_OBJS) -o $(NAME)

############
#   SFML   #
############
SFML_LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

$(NAME_SFML): $(SFML_OBJS)
	clang++ $(SFML_SRCS)  $(SFML_LDFLAGS) --shared -fPIC -o $(NAME_SFML) 


###########
# UTILITY #
###########

%.o: %.cpp
	clang++ $(CFLAGS) $< -c -o $@

run: $(NAME) $(NAME_SFML)
	./$(NAME)

run2: $(NAME) $(NAME_SFML)
	valgrind ./$(NAME)

clean:
	rm -f $(NAME) $(NAME_SFML)

fclean: clean
	rm -f *.o

re: fclean all
