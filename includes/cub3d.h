/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:00 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/20 17:12:44 by tabadawi         ###   ########.fr       */
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
# include <time.h>

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
# define ESC 		53
# define UP			126
# define DOWN		125
# define RIGHT		124
# define LEFT		123
# define W			13
# define A			0
# define S			1
# define D			2
# define PI			3.14159265359
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
# define INV_CF		"Invalid assignment of ceiling/floor.\n"
# define SMOL_MAP	"Map too small.\n"
# define NO_MAP		"Map doesn't exist.\n"
# define BAD_LMNT	"Bad element in map.\n"
# define XTRA_PLYR	"Broddie, you can only have one player.\n"
# define NO_PLYR	"Soo.... u dont wanna play??????????????\n"
# define VOID		"You cant go into the void bruv\n"
# define IMG		"Image could not load.\n"

/*****************************************************
*						structs						*
*****************************************************/

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
} t_keys;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_file
{
	char	**file;
	int		fd;
	int		file_size;
}	t_file;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	float	player_x;
	float	player_y;
	float	angle;
	char	player;
}	t_map;

typedef struct	s_txtr
{
	void	*north;
	void	*east;
	void	*west;
	void	*south;
	void	*ceiling;
	void	*floor;
}	t_txtr;

typedef struct	s_sprite
{
	void	*glow;
	void	*stick[5];
}	t_sprite;

typedef struct s_textures
{
	t_txtr		pointers;
	t_txtr		strings;
	int			floor;
	int			ceiling;
	int			f_arr[3];
	int			c_arr[3];
	t_sprite	s;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			counter;
	t_map		map;
	t_textures	textures;
	t_file		file;
	t_data		img;
	t_keys		keys;
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

int		empty_line(char *str);
void	free_array(char **arr);

//						execution					//
int		loops(t_game *game);
int		handle_hooks(t_game *game);
int		x_button(t_game *game);
int		keypress(int keysym, t_game *game);
int		keyrelease(int keysym, t_game *game);
int		move_player(t_game *game);
int		rotate_player(t_game *game);
void	rendermap(t_game *game);

void	rays(t_game *game);
void	raaaaays(t_game *game);

void	make_images(t_game *game);
int		animation(t_game *game);

int		close_game(t_game *game, int flag);

//						utils						//
void	errorer(void *ptr, int dimension, char *m);
char	*ft_free(char *str);

int		close_game(t_game *game, int flag);
void	init_game(t_game *game);
void	init_map(t_map *map);
void	init_textures(t_textures *textures);
void	pixel_put(t_data *data, int x, int y, int color);

#endif