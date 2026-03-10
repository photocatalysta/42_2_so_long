/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:19:23 by jsala             #+#    #+#             */
/*   Updated: 2024/03/04 14:39:46 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_fit(t_map *map, void *mlx_conn)
{
	int	screen_w;
	int	screen_h;

	screen_h = 0;
	screen_w = 0;
	mlx_get_screen_size(mlx_conn, &screen_w, &screen_h);
	if (map->map_size.x > screen_w / IMG_W
		|| map->map_size.y > screen_h / IMG_H)
	{
		throw_error("The map overflows the screen size; Please try a smaller map");
		return (0);
	}
	return (1);
}

int	check_map_size(t_map *map, void *mlx_conn)
{
	if (!(map->map_size.x) || !(map->map_size.y)
		|| !check_map_fit(map, mlx_conn))
	{
		throw_error("Map file Error");
		return (0);
	}
	return (1);
}

int	check_map(t_data *game, char *map_file)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map || !map_file)
		return (0);
	if (!load_map(map_file, game->map))
	{
		throw_error("Initialisation failure - Load Map");
		return (0);
	}
	game->map->map_size = get_map_size(game->map->map_content);
	if (!is_edge_walled(game->map->map_content, game->map->map_size))
	{
		throw_error("The map walls don't close the playable area");
		return (0);
	}
	if (!init_nr_objs(game->map))
	{
		throw_error("Map does not contain the minimum elements");
		game_exit(game);
		return (0);
	}
	if (!check_valid_path(game->map))
		return (0);
	return (1);
}
