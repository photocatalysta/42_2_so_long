/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:49:01 by jsala             #+#    #+#             */
/*   Updated: 2024/02/26 18:38:45 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_calloc(char *str, char *buff)
{
	if (!str || !buff)
	{
		if (str)
			free(str);
		if (buff)
			free(buff);
		exit (EXIT_FAILURE);
	}
}

void	throw_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	write(2, "\n", 1);
}

int	ft_check_file_extension(char *str)
{
	int	l_str;

	l_str = ft_strlen(str);
	if (l_str < 5)
	{
		throw_error("Correct input format: $>so_long *.ber.\n");
		return (0);
	}
	return (str[l_str - 4] == '.' && str[l_str - 3] == 'b'
		&& str[l_str - 2] == 'e' && str[l_str - 1] == 'r');
}

int	init_nr_objs(t_map *map)
{
	int	i;
	int	j;
	int	n_players;

	j = -1;
	n_players = 0;
	map->n_collecs = 0;
	map->n_exits = 0;
	while (map->map_content[++j])
	{
		i = -1;
		while (map->map_content[j][++i])
		{
			if (map->map_content[j][i] == 'E')
				map->n_exits += 1;
			else if (map->map_content[j][i] == 'C')
				map->n_collecs += 1;
			else if (map->map_content[j][i] == 'P')
			{
				map->p1_pos.x = i;
				map->p1_pos.y = j;
				n_players += 1;
			}
		}
	}
	return (n_players == 1 && map->n_collecs > 0 && map->n_exits == 1);
}

char	*get_file_path(char *base_file, int frame, char *suffix)
{
	char	*str;
	int		i;
	int		j;
	int		fd;

	str = ft_calloc(sizeof(char), ft_strlen(base_file) + ft_strlen(suffix) + 3);
	if (!str)
		return (NULL);
	i = -1;
	while (base_file[++i])
		str[i] = base_file[i];
	str[i++] = (char) frame + '0';
	j = -1;
	while (suffix[++j])
		str[i + j] = suffix[j];
	str[i + j + 1] = '\0';
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("The composed file name is not correctly pointing to an image", 2);
		free(str);
		return (NULL);
	}
	close(fd);
	return (str);
}
