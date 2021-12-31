/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:31:39 by kid-bouh          #+#    #+#             */
/*   Updated: 2021/12/31 20:32:06 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int		check_collects(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while(i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		key_press(int keycode, t_map *map)
{
	if(keycode == 53)
		exit(1);
	if(keycode == 13 || keycode == 126)
		movement(map, map->x - 1, map->y);
	if(keycode == 2 || keycode == 124)
		movement(map, map->x, map->y + 1);
	if(keycode == 0 || keycode == 123)
		movement(map, map->x, map->y - 1);
	if(keycode == 1 || keycode == 125)
		movement(map, map->x + 1, map->y);
	if(check_collects(map))
	{
		mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->img.exit1, map->y_exit * 50, map->x_exit * 50);
	}
	return (0);
}

void	movement(t_map *map, int x, int y)
{
	if (x < map->height && y < map->width)
	{
		if (map->map[x][y] != '1')
		{
			if (map->map[x][y] == 'E')
			{
				if(check_collects(map))
					exit(1);
			}
			else
			{
				map->map[map->x][map->y] = '0';
				map->x = x;
				map->y = y;
				map->map[x][y] = 'P';
				print_map(&map->mlx, map, &map->img);
			}
			map->count_move++;
			printf("%d\n",map->count_move);
		}
	}
}