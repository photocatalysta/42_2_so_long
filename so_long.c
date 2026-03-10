/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:20:39 by jsala             #+#    #+#             */
/*   Updated: 2024/02/26 20:30:36 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_mlx(t_data *game)
{
	init_keys(game);
	mlx_hook(game->window, ON_DESTROY, 0, game_exit, game);
	mlx_loop_hook(game->mlx_conn, ft_render, game);
	mlx_loop(game->mlx_conn);
	return (0);
}

int	init_game_resources(t_data *game)
{
	game->mlx_conn = mlx_init();
	if (!game->mlx_conn || !check_map_size(game->map, game->mlx_conn))
	{
		throw_error("The map is too big and doesn't fit the screen");
		return (0);
	}
	if (init_game_gui(game) == 0)
	{
		throw_error("Initialisation failure - Game GUI");
		return (0);
	}
	game->map->moves = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*game;

	if (argc != 2 || !ft_check_file_extension(argv[1]))
		return (EXIT_FAILURE);
	game = malloc(sizeof(t_data));
	if (!game)
		return (EXIT_FAILURE);
	if (check_map(game, argv[1]) == 0)
	{
		throw_error("Initialisation failure - Map");
		return (EXIT_FAILURE);
	}
	if (!init_game_resources(game))
		return (EXIT_FAILURE);
	handle_mlx(game);
	return (EXIT_SUCCESS);
}
