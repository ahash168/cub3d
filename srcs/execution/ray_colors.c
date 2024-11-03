/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:22:17 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 15:23:59 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	shade_floor(int colour, int y)
{
	float	shade_factor;
	t_trgb	new;
	int		check;

	check = WINDOW_H - y;
	if (check <= MINIMUMF)
		shade_factor = 1.f;
	else if (check >= MAXIMUMF)
		shade_factor = 0.f;
	else
	{
		shade_factor = 1.f - (((check) - MINIMUMF) / (MAXIMUMF - MINIMUMF));
		if (shade_factor < 0.f)
			shade_factor = 0.f;
		if (shade_factor > 1.f)
			shade_factor = 1.f;
	}
	new.trgb = colour;
	new.r = ((new.trgb >> 16) & 0xFF) * shade_factor;
	new.g = ((new.trgb >> 8) & 0xFF) * shade_factor;
	new.b = (new.trgb & 0xFF) * shade_factor;
	new.shaded = (new.trgb & 0xFF000000) | (new.r << 16) | (new.g << 8) | new.b;
	return (new.shaded);
}

int	change_shade(int colour, float dist, float avg)
{
	float			shade_factor;
	t_trgb			new;

	shade_factor = (dist <= MINIMUM) * 1.f + (dist >= MAXIMUM) * 0.f;
	if (dist > MINIMUM && dist < MAXIMUM)
	{
		shade_factor = avg;
		if (shade_factor < 0.0f)
			shade_factor = 0.0f;
		if (shade_factor > 1.0f)
			shade_factor = 1.0f;
	}
	new.trgb = colour;
	new.r = ((new.trgb >> 16) & 0xFF) * shade_factor;
	new.g = ((new.trgb >> 8) & 0xFF) * shade_factor;
	new.b = (new.trgb & 0xFF) * shade_factor;
	new.shaded = (new.trgb & 0xFF000000) | (new.r << 16) | (new.g << 8) | new.b;
	return (new.shaded);
}

int	get_pixel_color_from_texture(t_data *texture, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}
