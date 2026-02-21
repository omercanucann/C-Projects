/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:28 by oucan             #+#    #+#             */
/*   Updated: 2025/12/03 19:09:57 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364

typedef struct s_colors
{
	int	floor_red;
	int	floor_green;
	int	floor_blue;

	int	ceiling_red;
	int	ceiling_green;
	int	ceiling_blue;

	int	floor_color;
	int	ceiling_color;
}	t_colors;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_textures;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	int		initialized;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_y;
	double	ray_dir_x;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	double	wall_surface_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_ray;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		win_width;
	int		win_height;
}	t_mlx;

typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_textures	textures;
	t_colors	colors;
}	t_game;

typedef struct s_color_parse_result
{
	char	*trimed;
	char	*values;
	int		red;
	int		green;
	int		blue;
}	t_color_parse_result;

typedef struct s_flood
{
	int		height;
	int		width;
	char	*visited;
}			t_flood;

typedef struct s_bounds
{
	int	height;
	int	width;
}		t_bounds;

void	init_game(t_game *game);
void	clean_game(t_game *game);
void	print_error(char *message);
void	exit_error(char *message, t_game *game);
int		return_error(char *message);
void	free_map(t_map *map);
void	free_textures(t_textures *textures, void *mlx_ptr);
void	free_split(char **split);
int		init_mlx(t_game *game);
void	close_mlx(t_game *game);
int		parse_cub_file(char *file, t_game *game);
int		check_file_extension(char *filename);
char	**read_file_lines(int fd);
int		is_empty_line(char *line);
int		is_map_line(char *line);
int		parse_texture_line(char *line, t_map *map);
int		load_textures(t_game *game);
int		validate_texture_path(char *path);
int		load_single_texture(t_game *game, t_texture *texture, char *path);
int		parse_color_line(char *line, t_colors *colors);
int		parse_rgb_values(char *str, int *r, int *g, int *b);
int		create_color(int red, int green, int blue);
int		parse_map(char **lines, int start, t_game *game);
int		find_player_position(t_map *map, t_player *player);
void	init_player_direction(t_player *player, char direction);
int		get_map_width(char **grid);
int		validate_map(t_game *game);
int		check_walls_closed(t_map *map);
int		check_valid_characters(t_map *map);
int		flood_fill_check(t_map *map);
int		ft_isspace(char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);
int		helper(char **temp, char *line, char **lines, int count);
char	*ft_strtrim_whitespace(char *str);
int		is_wall(t_map *map, int x, int y);
int		flood_fill_check(t_map *map);
int		parse_map_and_validate(char **lines, int map_start, t_game *game);
int		parse_elements(char **lines, t_game *game, int *map_start);
char	**read_and_validate_file(char *file);
int		parse_cub_file(char *file, t_game *game);
int		get_color_values_from_line(char *line, t_color_parse_result *out);
int		create_color(int red, int green, int blue);
char	*readline_init(char *readone);
void	ray_cast(t_game *game, int i);
void	ray_pos(t_game *game);
int		render(void *param);
void	calculate_ray_steps(t_game *game);
void	draw_wall_column(t_game *game);
void	wall_size(t_game *game);
void	wall_draw_height(t_game *game);
int		get_wall_dir(t_game *game);
int		apply_texture(t_game *game, int y);
void	perform_dda(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		load_textures(t_game *game);
int		handle_player(t_map *map, t_player *player, int x, int y);
int		process_player_at(t_map *map, t_player *player, int x, int y);
int		search_player_in_map(t_map *map, t_player *player);
void	key_a_utils(int keycode, t_game *game);
void	key_w_utils(int keycode, t_game *game);
int		is_all_digits(char *s);
int		parse_components(char **parts, int *r, int *g, int *b);
char	*extract_and_validate_path(char *line);
int		set_ns_texture(char *line, t_map *map, char *path);
int		set_we_texture(char *line, t_map *map, char *path);
int		set_texture_by_prefix(char *line, t_map *map, char *path);
char	*extract_path(char *line);
int		is_valid_map_char(char c);
int		check_valid_characters(t_map *map);
int		get_map_height_from_grid(char **grid);
char	get_char(t_map *map, int y, int x);
int		check_single_component(t_map *map, int height, int width);
int		count_components(t_map *map, int height, int width);
int		get_map_width(char **grid);
char	get_ext_char(t_map *map, int y, int x, t_bounds *b);
void	flood_component(t_map *map, int y, int x, t_flood *f);
void	flood_outside(t_map *map, int y, int x, t_flood *f);
int		outside_cell_invalid(t_map *map, t_flood *f, int y, int x);
int		count_loop(t_map *map, t_flood *f, int height, int width);
int		process_component(t_map *map, t_flood *f, int y, int x);
#endif