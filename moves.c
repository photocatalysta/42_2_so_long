/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:08:13 by jsala             #+#    #+#             */
/*   Updated: 2024/01/28 09:17:00 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_obj	*update_obj_pos(t_map *map, t_obj *obj, t_pos new_pos)
{
	char	*moves_str;

	map->map_content[new_pos.y][new_pos.x] = obj->obj_char;
	map->map_content[obj->pos.y][obj->pos.x] = '0';
	obj->pos.x = new_pos.x;
	obj->pos.y = new_pos.y;
	map->moves += 1;
	moves_str = ft_itoa(map->moves);
	ft_putstr_fd("Current number of moves: ", 1);
	ft_putstr_fd(moves_str, 1);
	ft_putstr_fd(";\n", 1);
	free(moves_str);
	return (obj);
}

int	move_action(t_map *map, t_obj *obj, t_pos new_pos)
{
	char	obj_c;

	obj_c = map->map_content[new_pos.y][new_pos.x];
	if (obj_c == '1')
		return (1);
	else if (obj_c == 'C')
		player_collect(map);
	else if (obj_c == 'D')
		return (player_patrol());
	else if (obj_c == 'E')
		return (player_exit(map));
	update_obj_pos(map, obj, new_pos);
	return (1);
}

int	move(int keysim, t_obj *obj, t_map *map)
{
	t_pos	new_pos;

	new_pos.x = obj->pos.x;
	new_pos.y = obj->pos.y;
	if (keysim == UP || keysim == W)
		new_pos.y -= 1;
	else if (keysim == DOWN || keysim == S)
		new_pos.y += 1;
	else if (keysim == LEFT || keysim == A)
		new_pos.x -= 1;
	else if (keysim == RIGHT || keysim == D)
		new_pos.x += 1;
	return (move_action(map, obj, new_pos));
}
