/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:51:15 by jsala             #+#    #+#             */
/*   Updated: 2024/01/28 20:35:26 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_input(char *str)
{
	int	row_len;
	int	i;
	int	count;

	row_len = 0;
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'E' && str[i] != 'P'
			&& str[i] != 'C' && str[i] != 'D' && str[i] != '\n')
			return (0);
		if (str[i] == '\n')
		{
			if (row_len == 0)
				row_len = i;
			else if (row_len != count)
				return (0);
			count = 0;
		}
		else
			count++;
	}
	return (1);
}

int	is_edge_walled(char **map, t_pos size)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (i < size.x)
	{
		if (map[0][i] != '1' || map[size.y - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < size.y)
	{
		if (map[i][0] != '1' || map[i][size.x - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
