/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:14:52 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 11:32:45 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

// int	interpolate(int y, int inter[4])
// {
// 	if (inter[1] == inter[0])
// 	{
// 		printf("HEYO\n");
// 		return (inter[2]);
// 	}
// 	return (inter[2] + (inter[3] - inter[2]) * 
// 		(y - inter[0]) / (inter[1] - inter[0]));
// }

// void	fill(t_game *game, t_mini_player p)
// {
// 	int	y;
// 	int	x;

// 	y = p.init.y - 1;
// 	while (++y <= p.final.y)
// 	{
// 		p.init.x = interpolate(y, p.inter1);
// 		p.final.x = interpolate(y, p.inter2);
// 		if (p.init.x > p.final.x)
// 			ft_swap(&p.init.x, &p.final.x);
// 		x = p.init.x - 1;
// 		while (++x <= p.final.x)
// 			pixel_put(&game->img, x, y, 0xFFFFFF);
// 	}
// }

void	fill(t_game *game, t_mini_player p)
{
	int	y;
	int	x;

	y = p.init.y - 1;
	while (++y <= p.final.y)
	{
		if (p.inter1[1] == p.inter1[0])
			p.init.x = p.inter1[2];
		else
			p.init.x = p.inter1[2] + (p.inter1[3] - p.inter1[2]) * \
						(y - p.inter1[0]) / (p.inter1[1] - p.inter1[0]);
		if (p.inter2[1] == p.inter2[0])
			p.final.x = p.inter2[2];
		else
			p.final.x = p.inter2[2] + (p.inter2[3] - p.inter2[2]) * \
						(y - p.inter2[0]) / (p.inter2[1] - p.inter2[0]);
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
