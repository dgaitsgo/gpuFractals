NAME = fractal

SRC_DIR = ./src
OBJ_DIR = ./obs
INC_DIR = ./include
LIB_DIR = ./lib/libft

SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES = $(SRC_FILES:.c=.o)
INC_FILES = $(wildcard $(INC_DIR)*.h)

#compiles without flags
ERROR_FLAGS = -Wall -Werror -Wextra
FAST_FLAGS = -O3
DEBUG_FLAGS = -Og -g3
PROFILING_FLAGS = -pg

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_FILES)
	gcc -o $(NAME) $(OBJ_FILES) -L$(LIB_DIR) -lft -framework OpenCl -framework SDL2

%.o:%.c $(INC_FILES)
	gcc -c $(FAST_FLAGS) -I$(INC_DIR) $< -o $@

clean:
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all
