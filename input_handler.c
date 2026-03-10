/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:25:44 by jsala             #+#    #+#             */
/*   Updated: 2024/01/28 09:17:18 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key_input(int keysim, t_data *game)
{
	if (keysim == ESC)
		game_exit(game);
	else if (keysim == UP || keysim == RIGHT || keysim == LEFT
		|| keysim == DOWN || keysim == W || keysim == D
		|| keysim == A || keysim == S)
	{
		if (move(keysim, game->map->p1, game->map) == 0)
			game_exit(game);
	}
	return (0);
}

int	init_keys(t_data *game)
{
	mlx_key_hook(game->window, handle_key_input, game);
	return (1);
}
