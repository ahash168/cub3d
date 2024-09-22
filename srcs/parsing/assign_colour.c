/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_colour.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:52:44 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 22:02:42 by ahashem          ###   ########.fr       */
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

int	if_texture(t_game *game, char *str, char type)
{
	char	**txtr_arr;

	txtr_arr = NULL;
	if (type == 'C')
		txtr_arr = (char **)&game->textures.strings.ceiling;
	else
		txtr_arr = (char **)&game->textures.strings.floor;
	if (assign_texture(str, txtr_arr, game, 0))
	{
		if (type == 'C')
			game->textures.ceiling = 0;
		else
			game->textures.floor = 0;
		return (1);
	}
	return (0);
}

void	assign_colour(char *str, int *colour, int *arr, t_game *game)
{
	int		i;
	int		clr_counter;
	int		comma_counter;
	char	**temp;

	temp = ft_split(str, ' ');
	if (temp[0] && temp[1] && !temp[2])
		if (if_texture(game, str, temp[0][0]))
			return (free_array(temp));
	free_array(temp);
	i = 0;
	clr_counter = 0;
	comma_counter = 0;
	while (str[i] && (str[i] == ' ' || str[i] == 'F' || str[i] == 'C'))
	{
		if (str[i] == 'C' || str[i] == 'F')
		{
			i++;
			break ;
		}
		i++;
	}
	while (str[i])
	{
		if (str[i] && str[i] != ',' && str[i] != ' ' && !ft_isdigit(str[i]))
			errorer(game, 3, INV_CF);
		if (str[i] == ',')
			comma_counter++;
		if (ft_isdigit(str[i]))
		{
			i = set_colour(i, arr, clr_counter, str);
			clr_counter++;
			if (comma_counter != clr_counter - 1)
				errorer(game, 3, INV_CF);
		}
		if (i == -1 || clr_counter > 3)
			errorer(game, 3, INV_CF);
		i++;
	}
	if (clr_counter != 3 || comma_counter != 2)
		errorer(game, 3, INV_CF);
	(*colour) = create_rgb(arr);
}
