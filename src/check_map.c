/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:39:33 by kid-bouh          #+#    #+#             */
/*   Updated: 2021/12/31 20:32:15 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_error(void)
{
	ft_putstr("error !");
	exit(1);
}

int ft_strlen_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

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
		ft_error();
	while((line = get_next_line(fd)))
	{
		if(!width)
			width = ft_strlen_nl(line);
		if(width != ft_strlen_nl(line))
		{
			ft_putstr("error length map\n");
			exit(1);
		}
		height++;
	}
	map->height = height;
	map->width = width;
}

void	check_wall_map(t_map *map)
{
	int i;
	int	j;
	
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if(i == 0 || j == 0 || j == map->width - 1 || i == map->height - 1)
			{
				if(map->map[i][j] != '1')
				{
					printf("error map");
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

void	parsing_map(char *file, t_map *map)
{
	char	*line;
	int 	fd;
	int		i;

	i = 0;
	check_map(file, map);
	fd = open(file, O_RDONLY);
	if(fd < 0)
		ft_error();
	map->map = malloc(sizeof(char *) * (map->height + 1));
	map->map[map->height + 1] = NULL;
	while ((line = get_next_line(fd)))
	{
		map->map[i] = line;
		i++;
	}
	check_wall_map(map);
}

void	check_extension_map(char *map)
{
	int	i;
	
	i = ft_strlen(map);
	if (map[i - 1] != 'r' || map[i - 2] != 'e' || map[i - 3] != 'b' || map[i - 4] != '.')
	{
		ft_putstr("error format map\n");
		exit(1);
	}
}