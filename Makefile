NAME = nibbler

all: $(NAME)
	
build:
	meson build --prefix="${PWD}" --bindir="" --libdir="" 

$(NAME): build
	ninja install -C build

run: all
	./$(NAME) 15 20

run2: all
	valgrind ./$(NAME) 8 20

clean:
	ninja -C build clean || true

fclean: clean 
	ninja -C build uninstall || true

re: fclean all

.PHONY: $(NAME) all run run2 clean fclean re
