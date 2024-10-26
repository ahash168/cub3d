/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:46:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/26 21:50:02 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	x_button(t_game *game)
{
	(void) game;
	write(1, "Game over! You quit :p\n", 24);
	close_game(game, 0);
	return (0);
}

int	keypress(int keysym, t_game *game)
{
	if (keysym == ESC)
		close_game(game, 0);
	if (keysym == W)
		game->keys.w = 1;
	if (keysym == A)
		game->keys.a = 1;
	if (keysym == S)
		game->keys.s = 1;
	if (keysym == D)
		game->keys.d = 1;
	if (keysym == LEFT)
		game->keys.left = 1;
	if (keysym == RIGHT)
		game->keys.right = 1;
	if (keysym == E)
		doors(game);
	return (0);
}

int	keyrelease(int keysym, t_game *game)
{
	if (keysym == W)
		game->keys.w = 0;
	if (keysym == A)
		game->keys.a = 0;
	if (keysym == S)
		game->keys.s = 0;
	if (keysym == D)
		game->keys.d = 0;
	if (keysym == LEFT)
		game->keys.left = 0;
	if (keysym == RIGHT)
		game->keys.right = 0;
	return (0);
}

int	mouse(int x, int y, t_game *game)
{
	(void) y;
	if (game->keys.right && game->keys.left)
		return (0);
	if (x < (1920 / 8))
		game->keys.left = 1;
	else if (x > 7 * (1920 / 8))
		game->keys.right = 1;
	else
	{
		game->keys.left = 0;
		game->keys.right = 0;
	}
	return (0);
}
