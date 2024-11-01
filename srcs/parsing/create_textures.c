/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:23:38 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/01 22:23:38 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	xpm_img(t_game *game, char *file, t_data *data)
{
	(*data->img) = mlx_xpm_file_to_image(game->mlx, file, \
		&data->width, &data->height);
	if (!(*data->img))
		errorer(game, 3, XPM);
}

void	img_addr(t_data *data)
{
	data.addr = mlx_get_data_addr(data.img, &data.bpp, \
		&data.line_length, &data.endian);
}

// PLEASE FOR THE LOVE OF GOD IM CRYING PLEASE NORM THIS

void	create_textures(t_game *game, t_textures *textures)
{
	xpm_img(game, (char *)textures->strings.north, &textures->texture[N_N]);
	img_addr(textures->texture[N_N]);
	xpm_img(game, (char *)textures->strings.east, &textures->texture[E_N]);
	img_addr(textures->texture[E_N]);
	xpm_img(game, (char *)textures->strings.west, &textures->texture[W_N]);
	img_addr(textures->texture[W_N]);
	xpm_img(game, (char *)textures->strings.south, &textures->texture[S_N]);
	img_addr(textures->texture[S_N]);
	if (textures->strings.ceiling)
	{
		xpm_img(game, (char *)textures->strings.ceiling, \
			&textures->texture[C_N]);
		img_addr(textures->texture[C_N]);
	}
	if (textures->strings.floor)
	{
		xpm_img(game, (char *)textures->strings.floor, \
			&textures->texture[F_N]);
		img_addr(textures->texture[F_N]);
	}
	xpm_img(game, "./textures/xpm/wall.xpm", &textures->door);
	img_addr(textures->door);
}
