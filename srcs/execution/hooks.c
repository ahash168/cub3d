/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:46:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/25 13:51:30 by ahashem          ###   ########.fr       */
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
	// printf("%d\n", keysym);
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
	// if (keysym == 34)
	// {
	// 	printf("player\t%c\n", game->map.map[(int)game->map.player_y][(int)game->map.player_x]);
	// 	printf("up\t%c\n", game->map.map[(int)game->map.player_y - 1][(int)game->map.player_x]);
	// 	printf("down\t%c\n", game->map.map[(int)game->map.player_y + 1][(int)game->map.player_x]);
	// 	printf("left\t%c\n", game->map.map[(int)game->map.player_y][(int)game->map.player_x - 1]);
	// 	printf("right\t%c\n", game->map.map[(int)game->map.player_y][(int)game->map.player_x + 1]);
	// 	printf("angle\t%f\n", game->map.angle);
	// 	doors(game);
	// 	printf("\n");
	// 	printf("player\t%c\n", game->map.map[(int)game->map.player_y][(int)game->map.player_x]);
	// 	printf("up\t%c\n", game->map.map[(int)game->map.player_y - 1][(int)game->map.player_x]);
	// 	printf("down\t%c\n", game->map.map[(int)game->map.player_y + 1][(int)game->map.player_x]);
	// 	printf("left\t%c\n", game->map.map[(int)game->map.player_y][(int)game->map.player_x - 1]);
	// 	printf("right\t%c\n", game->map.map[(int)game->map.player_y][(int)game->map.player_x + 1]);
	// 	printf("angle\t%f\n\n\n", game->map.angle);
	// }
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
