/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:19:50 by jsala             #+#    #+#             */
/*   Updated: 2024/01/28 08:30:00 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_exit(t_map *map)
{
	if (map->n_collecs == 0)
	{
		ft_putstr_fd("Win!\n", 1);
		return (0);
	}
	ft_putstr_fd("Not all collectibles were gathered\n", 1);
	return (1);
}

int	player_collect(t_map *map)
{
	ft_putstr_fd("1 UP!\n", 1);
	if (!(map->n_collecs > 0))
		throw_error("Collectibles should be gone by now");
	map->n_collecs -= 1;
	return (0);
}

int	player_patrol(void)
{
	ft_putstr_fd("Game lost\n", 1);
	return (0);
}
