/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:00 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/22 18:21:00 by tabadawi         ###   ########.fr       */
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
# define USAGE		"Usage: ./cub3d [map_path].cub\n"
# define FILE_404	"File not found.\n"
# define TXTR_404	"Texture not found.\n"
# define EMPTY		"Empty file\n"
# define INVALID	"Invalid map file.\n"
# define INV_TXTR	"Invalid texture path\n"
# define XPM		"Invalid .xpm file\n"

/*****************************************************
*						structs						*
*****************************************************/

typedef struct s_file
{
	int		fd;
	int		file_size;
	char	**file;
}	t_file;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		player_x;
	int		player_y;
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

typedef struct s_textures
{
	t_txtr	pointers;
	t_txtr	strings;
	int		floor;
	int		ceiling;
	int		f_arr[3];
	int		c_arr[3];
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_textures	textures;
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
int		assign_texture(char *str, char **texture, t_game *game, int err_flag);

void	get_map(t_file *file, t_map *map, int index);
int		map_line(char *str, int flag);
void	validate_map(t_map *map);

int		empty_line(char *str);
void	free_array(char **arr);

int		minimap(t_game *game);
void	rendermap(t_game *game);

//						execution					//

int		x_button(t_game *game);
int		keypress(int keysym, t_game *game);

#endif