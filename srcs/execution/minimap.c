/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:35 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/27 22:12:21 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533f

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	interpolate(int y, int y1, int y2, int x1, int x2)
{
	if (y2 == y1)
		return (x1);
	return (x1 + (x2 - x1) * (y - y1) / (y2 - y1));
}

void	fill_triangle(t_game *game, int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
	if (y2 < y1)
	{
		ft_swap(&x1, &x2);
		ft_swap(&y1, &y2);
	}
	if (y3 < y1)
	{
		ft_swap(&x1, &x3);
		ft_swap(&y1, &y3);
	}
	if (y3 < y2)
	{
		ft_swap(&x2, &x3);
		ft_swap(&y2, &y3);
	}
	if (y2 != y1)
	{
		for (int y = y1; y <= y2; y++)
		{
			int	x_start = interpolate(y, y1, y2, x1, x2);
			int	x_end = interpolate(y, y1, y3, x1, x3);
			if (x_start > x_end)
				ft_swap(&x_start, &x_end);
			for (int x = x_start; x <= x_end; x++)
				pixel_put(&game->img, x, y, color);
		}
	}
	if (y3 != y2)
	{
		for (int y = y2; y <= y3; y++)
		{
			int	x_start = interpolate(y, y2, y3, x2, x3);
			int	x_end = interpolate(y, y1, y3, x1, x3);
			if (x_start > x_end)
				ft_swap(&x_start, &x_end);
			for (int x = x_start; x <= x_end; x++)
				pixel_put(&game->img, x, y, color);
		}
	}
}

void	draw_filled_arrow(t_game *game, int x_center, int y_center, float angle, int size, int color)
{
	int	tip_x = x_center + cosf(angle) * size;
	int	tip_y = y_center + sinf(angle) * size;
	int	base_left_x = x_center + cosf(angle + M_PI_2) * (size / 2);
	int	base_left_y = y_center + sinf(angle + M_PI_2) * (size / 2);
	int	base_right_x = x_center + cosf(angle - M_PI_2) * (size / 2);
	int	base_right_y = y_center + sinf(angle - M_PI_2) * (size / 2);
	int	center_x = (tip_x + base_left_x + base_right_x) / 3;
	int	center_y = (tip_y + base_left_y + base_right_y) / 3;
	int	dx = x_center - center_x;
	int	dy = y_center - center_y;

	tip_x += dx;
	tip_y += dy;
	base_left_x += dx;
	base_left_y += dy;
	base_right_x += dx;
	base_right_y += dy;
	fill_triangle(game, tip_x, tip_y, base_left_x, base_left_y, base_right_x, base_right_y, color);
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

void	draw_small(t_game *game, int x, int y, int draw_x, int draw_y)
{
	if (in_bounds(game, x, y))
	{
		if (game->map.map[y / 40][x / 40] == '1')
			pixel_put(&game->img, draw_x, draw_y, 0x9c9358);
		else if (game->map.map[y / 40][x / 40] == ' ')
			pixel_put(&game->img, draw_x, draw_y, 0x000000);
		else
			pixel_put(&game->img, draw_x, draw_y, 0x000000);
	}
	else
		pixel_put(&game->img, draw_x, draw_y, 0x000000);
}

void	draw_border(t_game *game)
{
	int	start_x = 40;
	int	start_y = 40;
	int	i = start_y;
	int	j = start_x;

	while (i < start_y + 320)
	{
		j = start_x;
		while (j < start_x + 320)
		{
			pixel_put(&game->img, j, i, 0xffffff);
			if ((j == start_x + 10) && ((i > start_y + 10) && (i < start_y + 310)))
				j += 300;
			else
				j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	i, j, x, y;
	int	draw_x, draw_y;

	i = game->map.player_y * 40;
	j = game->map.player_x * 40;
	y = i - 150;
	draw_y = 50;
	while (y < i + 150)
	{
		draw_x = 50;
		x = j - 150;
		while (x < j + 150)
		{
			draw_small(game, x, y, draw_x, draw_y);
			x++;
			draw_x++;
		}
		y++;
		draw_y++;
	}
	draw_border(game);
	draw_filled_arrow(game, 200, 200, game->map.angle, 20, 0xFFFFFF);
}

int	door_checker(t_game *game, int x, int y, char c)
{
	if (((game->map.angle <= 135 * DR && game->map.angle > 45 * DR) \
	&& game->map.map[y + 1][x] == c)
		|| ((game->map.angle <= 255 * DR && game->map.angle > 135 * DR) \
		&& game->map.map[y][x - 1] == c)
		|| ((game->map.angle <= 255 * DR && game->map.angle > 315 * DR) \
		&& game->map.map[y - 1][x] == c)
		|| (((game->map.angle <= 315 * DR && game->map.angle > 360 * DR) \
		|| (game->map.angle <= 45 * DR && game->map.angle > 0 * DR)) \
		&& game->map.map[y][x + 1] == c))
		return (1);
	return (0);
}

void	door_str(t_game *game)
{
	int		x;
	int		y;

	x = (int)game->map.player_x;
	y = (int)game->map.player_y;
	if (door_checker(game, x, y, 'D'))
		mlx_string_put(game->mlx, game->window, 960, 540, 0xFFFFFF, \
		"OPEN DOORRRR");
	else if (door_checker(game, x, y, 'O'))
		mlx_string_put(game->mlx, game->window, 960, 540, 0xFFFFFF, \
		"CLOSE DOORRRR");
}

void	rendermap(t_game *game)
{
	game->counter = (game->counter + 1) % (4 * 10);
	game->img.img = mlx_new_image(game->mlx, 1920, 1080);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, \
	&game->img.line_length, &game->img.endian);
	raaaaays(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, \
	game->img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, \
	game->textures.s.stick[game->counter / 10], 1100, 790);
	door_str(game);
	mlx_destroy_image(game->mlx, game->img.img);
}
