/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:35 by tabadawi          #+#    #+#             */
/*   Updated: 2024/11/03 11:28:04 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_player(t_game *game, int x_center, int y_center, float angle)
{
	t_mini_player	p;

	p.tip.x = x_center + cosf(angle) * 20;
	p.tip.y = y_center + sinf(angle) * 20;
	p.base_left.x = x_center + cosf(angle + M_PI_2) * 10;
	p.base_left.y = y_center + sinf(angle + M_PI_2) * 10;
	p.base_right.x = x_center + cosf(angle - M_PI_2) * 10;
	p.base_right.y = y_center + sinf(angle - M_PI_2) * 10;
	p.center.x = (p.tip.x + p.base_left.x + p.base_right.x) / 3;
	p.center.y = (p.tip.y + p.base_left.y + p.base_right.y) / 3;
	p.d.x = x_center - p.center.x;
	p.d.y = y_center - p.center.y;
	p.tip.x += p.d.x;
	p.tip.y += p.d.y;
	p.base_left.x += p.d.x;
	p.base_left.y += p.d.y;
	p.base_right.x += p.d.x;
	p.base_right.y += p.d.y;
	triangle(game, p);
}

int	in_bounds(t_game *game, int x, int y)
{
	if ((x / 40) >= 0 \
	&& (y / 40) >= 0 \
	&& (x / 40) < game->map.width \
	&& (y / 40) < game->map.height)
		return (1);
	return (0);
}

void	draw_border(t_game *game)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = 40;
	start_y = 40;
	j = start_x;
	i = start_y - 1;
	while (++i < start_y + 320)
	{
		j = start_x;
		while (j < start_x + 320)
		{
			pixel_put(&game->img, j, i, 0xffffff);
			if ((j == start_x + 10) && ((i > start_y + 10) \
			&& (i < start_y + 310)))
				j += 300;
			else
				j++;
		}
	}
}

void	draw_small(t_game *game, t_minimap m)
{
	if (in_bounds(game, m.x, m.y))
	{
		if (game->map.map[m.y / 40][m.x / 40] == '1')
			pixel_put(&game->img, m.draw_x, m.draw_y, 0x5e5e5d);
		else if (game->map.map[m.y / 40][m.x / 40] == ' ')
			pixel_put(&game->img, m.draw_x, m.draw_y, 0x000000);
		else if (game->map.map[m.y / 40][m.x / 40] == 'D')
			pixel_put(&game->img, m.draw_x, m.draw_y, 0x422b19);
		else
			pixel_put(&game->img, m.draw_x, m.draw_y, game->textures.floor);
	}
	else
		pixel_put(&game->img, m.draw_x, m.draw_y, 0x000000);
}

void	draw_minimap(t_game *game)
{
	t_minimap	m;

	m.i = game->map.player_y * 40;
	m.j = game->map.player_x * 40;
	m.y = m.i - 150;
	m.draw_y = 50;
	while (m.y < m.i + 150)
	{
		m.draw_x = 50;
		m.x = m.j - 150;
		while (m.x < m.j + 150)
		{
			draw_small(game, m);
			m.x++;
			m.draw_x++;
		}
		m.y++;
		m.draw_y++;
	}
	draw_border(game);
	draw_player(game, 200, 200, game->map.angle);
}
