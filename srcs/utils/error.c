/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:24:08 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/23 13:20:58 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_free(char *str)
{
	if (str)
		free(str);
	str = NULL;
	return (NULL);
}

char	**freeer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
	return (NULL);
}

void	error_message(char *m)
{
	write(2, m, ft_strlen(m));
}

void	errorer(void *ptr, int dimension, char *m)
{
	write(1, "--     Error.     --\n", 22);
	error_message(m);
	if (ptr && (dimension == 1))
		free(ptr);
	else if (dimension == 2)
		freeer((char **)ptr);
	else if (dimension == 3)
		close_game((t_game *)ptr, 1);
	exit(1);
}
