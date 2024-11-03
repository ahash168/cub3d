/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:00 by tabadawi          #+#    #+#             */
/*   Updated: 2024/11/03 14:34:24 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*****************************************************
*					libraries						*
*****************************************************/

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>

/*****************************************************
*					definitions						*
*****************************************************/

# define WALL		'1'
# define FLOOR		'0'
# define NORTH		'N'
# define EAST		'E'
# define WEST		'W'
# define SOUTH		'S'
# define DOOR		'D'
# define WINDOW_W	1920
# define WINDOW_H	1080
# define ESC 		53
# define UP			126
# define DOWN		125
# define RIGHT		124
# define LEFT		123
# define W			13
# define A			0
# define S			1
# define D			2
# define E			14
# define DR			0.0174533f
# define MINIMUM	50.f
# define MAXIMUM	350.f
# define MINIMUMF	50.f
# define MAXIMUMF	350.f
# define MALLOC		"ur such a failure, computer! ;p L\n"
# define USAGE		"Usage: ./cub3d [map_path].cub\n"
# define FILE_404	"File not found.\n"
# define TXTR_404	"Texture not found.\n"
# define EMPTY		"Empty file.\n"
# define INVALID	"Invalid map file.\n"
# define INV_TXTR	"Invalid texture path.\n"
# define XPM		"Invalid .xpm file.\n"
# define NOT_TXTR	"Non-texture found in file.\n"
# define CANT_TXTR	"Couldn't get all textures.\n"
# define DOOR_ERR	"Door needs to be between exactly 2 walls.\n"
# define INV_CF		"Invalid assignment of ceiling/floor.\n"
# define SMOL_MAP	"Map too small.\n"
# define NO_MAP		"Map doesn't exist.\n"
# define BAD_LMNT	"Bad element in map.\n"
# define XTRA_PLYR	"Broddie, you can only have one player.\n"
# define NO_PLYR	"Soo.... u dont wanna play??????????????\n"
# define VOID		"You cant go into the void bruv\n"
# define IMG		"Image could not load.\n"

enum e_type
{
	N_N,
	E_N,
	W_N,
	S_N,
	C_N,
	F_N
};

/*****************************************************
*						structs						*
*****************************************************/

typedef struct s_minimap
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;
}	t_minimap;

typedef struct s_trig_xy
{
	int	x;
	int	y;
}	t_trig_xy;

typedef struct s_mini_player
{
	t_trig_xy	tip;
	t_trig_xy	base_left;
	t_trig_xy	base_right;
	t_trig_xy	center;
	t_trig_xy	d;
	t_trig_xy	init;
	t_trig_xy	final;
	int			inter1[4];
	int			inter2[4];
}	t_mini_player;

typedef struct s_trgb
{
	unsigned int	trgb;
	unsigned int	shaded;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_trgb;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_data;

typedef struct s_file
{
	char	**file;
	int		fd;
	int		file_size;
}	t_file;

typedef struct s_door
{
	int	open;
	int	x;
	int	y;
}	t_door;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	float	player_x;
	float	player_y;
	float	angle;
	char	player;
	t_door	**doors;
}	t_map;

typedef struct s_txtr
{
	void	*north;
	void	*east;
	void	*west;
	void	*south;
	void	*ceiling;
	void	*floor;
}	t_txtr;

typedef struct s_sprite
{
	void	*glow;
	void	*stick[5];
}	t_sprite;

typedef struct s_textures
{
	t_data		texture[6];
	t_data		door;
	t_txtr		strings;
	int			floor;
	int			ceiling;
	int			f_arr[3];
	int			c_arr[3];
	t_sprite	s;
}	t_textures;

typedef struct s_ray_data
{
	float	h_inter;
	float	v_inter;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	distance;
	float	fisheye;
	float	wall_h;
	int		door_flag_h;
	int		door_flag_v;
	float	intercept;
	t_data	*current_texture;
}	t_ray_data;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			counter;
	float		fov_rd;
	float		offset;
	float		wall_factor;
	t_map		map;
	t_textures	textures;
	t_file		file;
	t_data		img;
	t_keys		keys;
	t_ray_data	rays[WINDOW_W];
}	t_game;

/*****************************************************
*					functions						*
*****************************************************/

//						parsing						//
void	parsing(char *path, t_game *game);

void	validate_file(char *path, t_file *file);
void	get_file(char *path, t_file *file);

int		get_textures(t_file *file, t_textures *textures, t_game *game);
int		collected_textures(t_textures *textures);

void	assign_colour(char *str, int *colour, int *arr, t_game *game);
int		set_colour(int i, int *arr, int clr_counter, char *str);
int		create_rgb(int *color_arr);
int		assign_texture(char *str, char **texture, t_game *game, int err_flag);

void	get_map(t_game *game, t_map *map, int index);
int		map_line(char *str, int flag, t_game *game);
void	validate_map(t_map *map, t_game *game);
void	create_textures(t_game *game, t_textures *textures);

int		empty_line(char *str);
void	free_array(char **arr);

//						execution					//
int		loops(t_game *game);
int		handle_hooks(t_game *game);
int		x_button(t_game *game);
int		keypress(int keysym, t_game *game);
int		keyrelease(int keysym, t_game *game);
int		mouse(int x, int y, t_game *game);
int		move_player(t_game *game);
int		rotate_player(t_game *game);

void	rays(t_game *game, t_ray_data *ray_arr);

void	init_ray(t_ray_data *ray);
void	setup_ray(t_game *game, t_ray_data *ray, float angle);

int		get_v_inter(t_game *game, float ray_angle, t_ray_data *ray);
int		get_h_inter(t_game *game, float ray_angle, t_ray_data *ray);

void	draw_vertical_line(t_game *game, int x, t_ray_data *ray);

void	limit_angle(float *angle, float offset);

void	rendermap(t_game *game);
void	draw_minimap(t_game *game);
void	triangle(t_game *game, t_mini_player p);

void	make_images(t_game *game);
void	doors(t_game *game);
void	door_str(t_game *game);

//						utils						//
void	errorer(void *ptr, int dimension, char *m);
char	*ft_free(char *str);

int		close_game(t_game *game, int flag);
void	init_game(t_game *game);
void	init_map(t_map *map);
void	init_textures(t_textures *textures);
void	pixel_put(t_data *data, int x, int y, int color);

void	destroy_images(t_game *game);

#endif