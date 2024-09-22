/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_colour.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:52:44 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 18:09:43 by tabadawi         ###   ########.fr       */
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

void	assign_colour(char *str, int *colour, int *arr, t_game *game)
{
	int		i;
	int		clr_counter;
	int		comma_counter;
	char	**temp;

	temp = ft_split(str, ' ');
	if (temp[0] && temp[1] && !temp[2])
	{
		if (temp[0][0] == 'C')
		{
			if (assign_texture(str, (char **)&game->textures.strings.ceiling, game, 0))
			{
				game->textures.ceiling = 0;
				return (free_array(temp));
			}
		}
		else if (temp[0][0] == 'F')
		{
			if (assign_texture(str, (char **)&game->textures.strings.floor, game, 0))
			{
				game->textures.floor = 0;
				return (free_array(temp));
			}
		}
	}
	free_array(temp);
	clr_counter = 0;
	comma_counter = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == 'F' || str[i] == 'C'))
	{
		if (str[i] == 'C' || str[i] == 'F')
		{
			i++;
			break;
		}
		i++;
	}
	while (str[i])
	{
		//free file and current allocated textures
		if (str[i] && str[i] != ',' && str[i] != ' ' && !ft_isdigit(str[i]))
			(printf("%c: not for the colour\n", str[i]), exit(1));
		if (str[i] == ',')
			comma_counter++;
		if (ft_isdigit(str[i]))
		{
			i = set_colour(i, arr, clr_counter, str);
			clr_counter++;
			if (comma_counter != clr_counter - 1)
				(printf("wrong count\n"), exit(1));
		}
		if (i == -1)
			(printf("colour problem\n"), exit(1));
		if (clr_counter > 3)
			(printf("wrong count\n"), exit(1));
		i++;
	}
	if (clr_counter != 3 || comma_counter != 2)
		(printf("colour problem\n"), exit(1));
	(*colour) = create_rgb(arr);
}
