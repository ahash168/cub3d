/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:44:30 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 22:04:01 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	create_rgb(int *color_arr)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = color_arr[0];
	g = color_arr[1];
	b = color_arr[2];
	a = 0x00000000;
	return (r << 16 | g << 8 | b | a);
}

int	set_colour(int i, int *arr, int clr_counter, char *str)
{
	int		index;
	char	colour[4];

	index = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (index > 2)
			return (-1);
		colour[index++] = str[i++];
	}
	colour[index] = '\0';
	arr[clr_counter] = ft_atoi(colour);
	if (arr[clr_counter] > 255)
		return (-1);
	return (i - 1);
}
