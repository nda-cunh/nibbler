NAME = nibbler

all: $(NAME)
	
build/ninja:
	meson build --prefix="${PWD}" --bindir="" --libdir="" --wipe

$(NAME): build/ninja
	ninja install -C build

run: all
	./$(NAME) 15 20

run2: all
	valgrind ./$(NAME) 8 20

clean:
	ninja -C build clean

fclean: clean 
	ninja -C build uninstall

re: fclean all

.PHONY: $(NAME) all run run2 clean fclean re
