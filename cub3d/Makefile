NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./include -I./libft -I./mlx

MLX_FLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

LIBFT = ./libft/libft.a
MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx.a

SRC_DIR = src
OBJ_DIR = obj

SOURCES = main.c \
			utils/error.c \
			utils/memory.c \
			utils/mlx_utils.c \
			utils/init.c \
			utils/clean.c \
			utils/get_next_line.c \
			utils/utils.c \
			parsing/cub_file.c \
			parsing/parse_file_helper.c \
			parsing/parse_file.c \
			parsing/tissue.c \
			parsing/tissue_helper.c \
			parsing/parse_color_helper.c \
			parsing/load.c \
			parsing/parse_color.c \
			parsing/parse_map.c \
			parsing/parse_map_two.c \
			parsing/validate_map.c \
			parsing/validate_map_utils.c \
			parsing/cub_file_two.c \
			parsing/parse_color_two.c \
			parsing/flood_fill.c \
			render/draw_walls.c \
			render/render.c \
			raycasting/dda_algoritm.c \
			raycasting/raycast.c \
			raycasting/texture_mapping.c \
			input/keyboard.c \
			input/keyboard_utils.c


OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ cub3D compiled successfully!"

$(MINILIBX):
	@printf "🔧 Building minilibx in %s\n" $(MINILIBX_DIR)
	@$(MAKE) -C $(MINILIBX_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	rm -rf $(OBJ_DIR)
	@make -C libft clean
	@make -C $(MINILIBX_DIR) clean || true
	@echo "🧹 Object files cleaned"

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean
	@make -C $(MINILIBX_DIR) fclean || true
	@echo "🧹 Executable removed"

re: fclean all

.PHONY: all clean fclean re
