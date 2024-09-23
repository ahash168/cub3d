/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:46:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/23 13:22:15 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_game(t_game *game, int flag)
{
	if (game->file.file)
		free_array(game->file.file);
	if (game->map.map)
		free_array(game->map.map);
	ft_free(game->textures.strings.north);
	ft_free(game->textures.strings.east);
	ft_free(game->textures.strings.west);
	ft_free(game->textures.strings.south);
	ft_free(game->textures.strings.ceiling);
	ft_free(game->textures.strings.floor);
	// mlx_destroy_window(game->mlx, game->window);
	exit (flag);
}

int	x_button(t_game *game)
{
	(void) game;
	write(1, "Game over! You quit :p\n", 24);
	close_game(game, 0);
	return (0);
}

int	keypress(int keysym, t_game *game)
{
	(void) game;
	if (keysym == ESC)
	{
		// write(1, "Game over! You quit :p\n", 24);
		close_game(game, 0);
	}
	else
	{
		write(1, "moooove\n", 9);
		// movement move()
		return (0);
	}
	return (0);
}
