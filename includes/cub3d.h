/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/17 22:21:33 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "../mlx/mlx.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65363
# define KEY_RIGHT 65361

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_MOUSE_PRESS 4
# define EVENT_MOUSE_RELEASE 5
# define EVENT_MOUSE_MOVE 6
# define EVENT_EXIT 17

# define MOVE_SPEED 0.01
# define ROT_SPEED 0.005

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_texture
{
	char	*path;
	t_img	img;
}			t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	value;
}		t_color;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	tex_pos;
	double	tex_step;
}			t_ray;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
}			t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	player_dir;
}			t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_texture	textures[4];
	t_color		floor;
	t_color		ceiling;
	int			**tex_buf;
}				t_game;

/* main.c */
int		main(int argc, char **argv);

/* init.c */
void	init_game(t_game *game);
void	init_player(t_game *game);

/* init2.c */
void	init_textures(t_game *game);
void	init_window(t_game *game);

/* parser/parse_map.c */
int		parse_map(t_game *game, char *file_path);
int		read_map_file(t_game *game, char *file_path);
int		validate_file_extension(char *file_path);

/* parser/validate_map.c */
int		validate_map(t_game *game);
int		check_walls(t_map *map);
int		check_player(t_map *map);

/* parser/parse_textures.c */
int		parse_texture_line(t_game *game, char *line);
int		load_textures(t_game *game);

/* parser/parse_colors.c */
int		parse_color_line(t_game *game, char *line);
int		create_rgb(t_color *color);

/* rendering/render.c */
int		render_frame(t_game *game);
void	draw_floor_ceiling(t_game *game);

/* rendering/raycasting.c */
void    raycasting(t_game *game);
void    init_ray(t_game *game, t_ray *ray, int x);
void    perform_dda(t_game *game, t_ray *ray);
void    calculate_wall_distance(t_ray *ray);
void    calculate_wall_height(t_ray *ray);

/* rendering/textures.c */
void	calculate_wall_texture(t_game *game, t_ray *ray);
void	draw_wall_texture(t_game *game, t_ray *ray, int x);

/* rendering/draw.c */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_line(t_game *game, int x, t_ray *ray);

/* player/move.c */
void	move_player(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

/* player/rotate.c */
void	rotate_player(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	set_player_direction(t_game *game, char dir);

/* events/key_handler.c */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);

/* events/exit_handler.c */
int		exit_game(t_game *game);
void	free_resources(t_game *game);

/* utils/error.c */
void	error_exit(char *message);
void	print_error(char *message);

/* utils/memory.c */
void	free_map(t_map *map);
char	**allocate_grid(int height, int width);

/* utils/math_utils.c */
double	deg_to_rad(double angle);
//int		is_wall(t_map *map, int x, int y);

/* utils/string_utils.c */
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

/* mlx/mlx_wrapper.c */
void	*mlx_init_wrapper(void);
void	*mlx_new_window_wrapper(void *mlx_ptr, int width, int height, char *title);
void	*mlx_new_image_wrapper(void *mlx_ptr, int width, int height);
int		mlx_hook_wrapper(void *win_ptr, int event, int mask, int (*f)(), void *param);

#endif