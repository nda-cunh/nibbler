NAME = nibbler

all: $(NAME)
	
DEPENDENCIES = raylib sfml libsdl2

suprapack:
	@INSTALL_DEPS= ; \
	for dep in $(DEPENDENCIES); do \
		if ! suprapack info $$dep >/dev/null; then \
			INSTALL_DEPS="$$INSTALL_DEPS $$dep" ; \
		fi; \
	done; \
	if [ -n "$$INSTALL_DEPS" ]; then \
		suprapack install $$INSTALL_DEPS --force --yes; \
	fi

build: suprapack
	@meson build --prefix="${PWD}" --bindir="" --libdir="" 

$(NAME): build
	ninja install -C build

run: all
	./$(NAME) -h 10 -w 10

run2: all
	valgrind --leak-check=full ./$(NAME) -h 10 -w 10

run3: all
	@read -p "Enter the width:  " width; \
	 read -p "Enter the height: " height; \
	./$(NAME) $$width $$height

clean:
	ninja -C build clean || true

fclean: clean 
	ninja -C build uninstall || true

re: fclean all

.PHONY: $(NAME) all run run2 clean fclean re suprapack
