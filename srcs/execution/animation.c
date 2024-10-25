/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:13:06 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/18 20:32:48 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	find_sprite(int n, void *img, void **imgs)
{
	int	x;

	x = 0;
	while (x < n)
	{
		if (img == imgs[x++])
			break ;
	}
	return (x);
}

int	animation(t_game *game)
{
	void	**img;
	void	**imgs;
	int		x;

	img = &(game->textures.s.glow);
	imgs = (void **)game->textures.s.stick;
	x = find_sprite(4, game->textures.s.glow, game->textures.s.stick);
	if (game->textures.s.glow == game->textures.s.stick[4])
		game->textures.s.glow = game->textures.s.stick[0];
	else
		game->textures.s.glow = game->textures.s.stick[x];
	mlx_put_image_to_window(game->mlx, game->window, game->textures.s.glow, 1100, 790);
	// put_allimg(game, game->textures.s.glow, 'x');
	return (0);
}
