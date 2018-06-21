ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = ft_malloc

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDE_DIR = ./includes

DIR_LIB = ./libft/

SRC_DIR = ./srcs/

FILES = malloc.c \
		utils.c \
		free.c \
		show_alloc_mem.c \
		show_alloc_mem_ex.c \
		realloc.c \
		calloc.c

SRCS = $(addprefix $(SRC_DIR), $(FILES))

all:
	@ make -C $(DIR_LIB)
	@ $(CC) $(CFLAGS) -shared -o libft_malloc_$(HOSTTYPE).so $(SRCS) -L $(DIR_LIB) -lft -lpthread -I $(INCLUDE_DIR)
	@ echo "Library created: \033[32mlibft_malloc_$(HOSTTYPE).so\033[0m"
	@ ln -s libft_malloc_$(HOSTTYPE).so libft_malloc.so
	@ echo "Link file created: \033[32mlibft_malloc.so\033[0m"
	@ echo "\033[32mAll done!\033[0m"

test:
	@ make -C $(DIR_LIB)
	@ $(CC) $(CFLAGS) $(SRCS) -I$(INCLUDE_DIR) -o ft_malloc -L ./libft/ -lft -lpthread -g
	@ echo "test binary created"

clean:
	@ make clean -C $(DIR_LIB)
	@ rm libft_malloc.so
	@ echo "\033[32mLink file removed\033[0m"

fclean: clean
	@ make fclean -C $(DIR_LIB)
	@ rm libft_malloc_$(HOSTTYPE).so
	@ echo "\033[32mLibrary removed\033[0m"

re: fclean all

.PHONY : all clean fclean re