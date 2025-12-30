NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# MinilibX
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

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
      $(SRC_DIR)/textures/load_textures.c \
      $(SRC_DIR)/init/init_mlx.c \
      $(SRC_DIR)/utils/error.c \
      $(SRC_DIR)/utils/ft_strlen.c \
      $(SRC_DIR)/utils/ft_strdup.c \
      $(SRC_DIR)/utils/ft_strtrim.c \
      $(SRC_DIR)/utils/skip_spaces.c \
      $(SRC_DIR)/utils/is_empty_line.c\
      $(SRC_DIR)/init/init_player.c\
      $(SRC_DIR)/raycasting/raycasting.c\
      $(SRC_DIR)/rendering/draw.c\
      $(SRC_DIR)/rendering/render.c\
      $(SRC_DIR)/events/keyboard.c\

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re