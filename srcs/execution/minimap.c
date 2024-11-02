/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:35 by tabadawi          #+#    #+#             */
/*   Updated: 2024/11/02 18:50:21 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533f

typedef struct s_trig_xy
{
	int	x;
	int	y;
}	t_trig_xy;

typedef struct s_mini_player
{
	t_trig_xy	tip;
	t_trig_xy	base_left;
	t_trig_xy	base_right;
	t_trig_xy	center;
	t_trig_xy	d;
	t_trig_xy	init;
	t_trig_xy	final;
	int			inter1[4];
	int			inter2[4];
}	t_mini_player;

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	swapper(t_mini_player *p)
{
	if (p->base_left.y < p->tip.y)
	{
		ft_swap(&p->tip.x, &p->base_left.x);
		ft_swap(&p->tip.y, &p->base_left.y);
	}
	if (p->base_right.y < p->tip.y)
	{
		ft_swap(&p->tip.x, &p->base_right.x);
		ft_swap(&p->tip.y, &p->base_right.y);
	}
	if (p->base_right.y < p->base_left.y)
	{
		ft_swap(&p->base_left.x, &p->base_right.x);
		ft_swap(&p->base_left.y, &p->base_right.y);
	}
}

int	interpolate(int y, int inter[4])
{
	if (inter[1] == inter[0])
	{
		printf("HEYO\n");
		return (inter[2]);
	}
	return (inter[2] + (inter[3] - inter[2]) * \
	(y - inter[0]) / (inter[1] - inter[0]));
}

void	fill(t_game *game, t_mini_player p)
{
	int	y;
	int	x;

	y = p.init.y - 1;
	while (++y <= p.final.y)
	{
		p.init.x = interpolate(y, p.inter1);
		p.final.x = interpolate(y, p.inter2);
		if (p.init.x > p.final.x)
			ft_swap(&p.init.x, &p.final.x);
		x = p.init.x - 1;
		while (++x <= p.final.x)
			pixel_put(&game->img, x, y, 0xFFFFFF);
	}
}

void	assign_inter(t_mini_player *p, int flag)
{
	p->inter2[0] = p->tip.y;
	p->inter2[1] = p->base_right.y;
	p->inter2[2] = p->tip.x;
	p->inter2[3] = p->base_right.x;
	if (flag == 1)
	{
		p->inter1[0] = p->tip.y;
		p->inter1[1] = p->base_left.y;
		p->inter1[2] = p->tip.x;
		p->inter1[3] = p->base_left.x;
	}
	else if (flag == 2)
	{
		p->inter1[0] = p->base_left.y;
		p->inter1[1] = p->base_right.y;
		p->inter1[2] = p->base_left.x;
		p->inter1[3] = p->base_right.x;
	}
}

void	triangle(t_game *game, t_mini_player p)
{
	swapper(&p);
	if (p.base_left.y != p.tip.y)
	{
		assign_inter(&p, 1);
		p.init.y = p.tip.y;
		p.final.y = p.base_left.y;
		fill(game, p);
	}
	if (p.base_right.y != p.base_left.y)
	{
		assign_inter(&p, 2);
		p.init.y = p.base_left.y;
		p.final.y = p.base_right.y;
		fill(game, p);
	}
}

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

typedef struct s_minimap
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;
}	t_minimap;

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

int	door_checker(t_game *game, int x, int y, char c)
{
	if (((game->map.angle <= 135 * DR && game->map.angle > 45 * DR) \
		&& game->map.map[y + 1][x] == c)
		|| ((game->map.angle <= 255 * DR && game->map.angle > 135 * DR) \
		&& game->map.map[y][x - 1] == c)
		|| ((game->map.angle <= 315 * DR && game->map.angle > 255 * DR) \
		&& game->map.map[y - 1][x] == c)
		|| (((game->map.angle <= 360 * DR && game->map.angle > 315 * DR) \
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
		"OPEN DOORRRR [E]");
	else if (door_checker(game, x, y, 'O'))
		mlx_string_put(game->mlx, game->window, 960, 540, 0xFFFFFF, \
		"CLOSE DOORRRR [E]");
}

void	rendermap(t_game *game)
{
	game->counter = (game->counter + 1) % (4 * 10);
	game->img.img = mlx_new_image(game->mlx, 1920, 1080);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, \
	&game->img.line_length, &game->img.endian);
	rays(game, game->rays);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, \
	game->img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, \
	game->textures.s.stick[game->counter / 10], 1100, 790);
	door_str(game);
	mlx_destroy_image(game->mlx, game->img.img);
}
