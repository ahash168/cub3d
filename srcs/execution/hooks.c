/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:46:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/02 11:15:47 by ahashem          ###   ########.fr       */
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
