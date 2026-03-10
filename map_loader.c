/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:47:27 by jsala             #+#    #+#             */
/*   Updated: 2024/02/26 20:17:26 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_pos	get_map_size(char **map)
{
	t_pos	size;

	size.x = 0;
	size.y = 0;
	while (map[size.y])
		size.y++;
	while (map[0][size.x])
		size.x++;
	return (size);
}

char	**read_mapfile(int fd)
{
	char	*buff;
	char	*str;
	char	*old_str;
	char	**map;

	buff = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buff)
		exit(EXIT_FAILURE);
	str = ft_calloc(sizeof(char), 1);
	check_calloc(buff, str);
	str[0] = '\0';
	buff[BUFFER_SIZE] = '\0';
	while (read(fd, buff, BUFFER_SIZE))
	{
		old_str = str;
		str = ft_strjoin(old_str, buff);
		free(old_str);
		if (!str)
			exit(EXIT_FAILURE);
	}
	free(buff);
	if (ft_strlen(str) < 5 || !check_input(str))
	{
		free(str);
		write(2, "Error\nThe input map is not valid\n", 32);
		return (NULL);
	}
	map = ft_split(str, '\n');
	free(str);
	return (map);
}

int	load_map(char *file, t_map *map)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		throw_error("Error opening the file, invalid fd");
		return (0);
	}
	map->map_content = read_mapfile(fd);
	if (!(map->map_content))
	{
		throw_error("Error loading map content");
		return (0);
	}
	close(fd);
	return (1);
}
