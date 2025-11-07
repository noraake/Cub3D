NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
OBJ_DIR = obj

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/parsing/parse_file.c \
      $(SRC_DIR)/parsing/read_file.c \
      $(SRC_DIR)/parsing/parse_textures.c \
      $(SRC_DIR)/parsing/parse_colors.c \
      $(SRC_DIR)/parsing/parse_map.c \
      $(SRC_DIR)/parsing/find_player.c \
      $(SRC_DIR)/parsing/validate_map.c \
      $(SRC_DIR)/parsing/free_game.c \
      $(SRC_DIR)/utils/error.c \
      $(SRC_DIR)/utils/ft_strlen.c \
      $(SRC_DIR)/utils/ft_strdup.c \
      $(SRC_DIR)/utils/ft_strtrim.c \
      $(SRC_DIR)/utils/skip_spaces.c \
      $(SRC_DIR)/utils/is_empty_line.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
