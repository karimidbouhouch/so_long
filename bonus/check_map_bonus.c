/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:44:17 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/01/03 18:29:46 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	check_map(char *file, t_map	*map)
{
	char	*line;
	int		fd;
	int		width;
	int		height;

	width = 0;
	height = 0;
	check_extension_map(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_putstr("error read map\n");
	while (ft_read(fd, &line))
	{
		if (!width)
			width = ft_strlen_nl(line);
		if (width != ft_strlen_nl(line))
		{
			ft_putstr("map structure error\n");
			exit(1);
		}
		height++;
	}
	map->height = height;
	map->width = width;
}

void	check_wall_map_2(t_map *map)
{
	if (check_char(map, 'P') > 1 || check_char(map, 'P') == 0)
	{
		ft_putstr("Player error !");
		exit(1);
	}
	if (check_char(map, 'C') == 0)
	{
		ft_putstr("Collect error !");
		exit(1);
	}
	if (check_char(map, 'E') == 0)
	{
		ft_putstr("Exit error !");
		exit(1);
	}
}

void	check_wall_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (i == 0 || j == 0 || j == map->width - 1 || i == map->height - 1)
			{
				if (map->map[i][j] != '1')
				{		
					ft_putstr("error map");
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
	check_wall_map_2(map);
}

void	parsing_map(char *file, t_map *map)
{
	char	*line;
	char	*path;
	int		fd;
	int		i;

	i = 0;
	path = ft_strjoin("maps/", file);
	check_map(path, map);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_putstr("error read map\n");
	map->map = malloc(sizeof(char *) * (map->height + 1));
	map->map[map->height + 1] = NULL;
	while (ft_read(fd, &line))
	{
		map->map[i] = line;
		i++;
	}
	free(path);
	check_wall_map(map);
}

void	check_extension_map(char *map)
{
	int	i;

	i = ft_strlen(map);
	if (map[i - 1] != 'r' || map[i - 2] != 'e'
		|| map[i - 3] != 'b' || map[i - 4] != '.')
	{
		ft_putstr("error map\n");
		exit(1);
	}
}
