/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:47:35 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/01/04 00:04:26 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	*init_image(char *file, t_mlx *mlx)
{
	void	*image;
	int		width;
	int		height;

	width = 0;
	height = 0;
	image = mlx_xpm_file_to_image(mlx->mlx_ptr, file, &width, &height);
	if (width == 0 || width == 0)
	{
		printf("error img");
		exit(1);
	}
	return (image);
}

void	init_images(t_mlx *mlx, t_img *img)
{
	img->empty = init_image("img/empty.xpm", mlx);
	img->collect = init_image("img/collect.xpm", mlx);
	img->wall = init_image("img/wall.xpm", mlx);
	img->player1 = init_image("img/player1.xpm", mlx);
	img->player2 = init_image("img/player2.xpm", mlx);
	img->exit = init_image("img/exit.xpm", mlx);
	img->enemy = init_image("img/enemy.xpm", mlx);
}

void	print_map2(t_map *map, int i, int j, char *player)
{
	if (map->map[i][j] == 'P')
	{
		map->x = i;
		map->y = j;
		mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
			player, j * 50, i * 50);
	}
	if (map->map[i][j] == 'E')
	{
		mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
			map->img.exit, j * 50, i * 50);
	}
	if (map->map[i][j] == 'C')
		mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
			map->img.collect, j * 50, i * 50);
	if (map->map[i][j] == 'M')
	{
		mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
			map->img.enemy, j * 50, i * 50);
	}
}

void	print_map(t_map *map, char *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == '1')
				mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
					map->img.wall, j * 50, i * 50);
			if (map->map[i][j] == '0' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'P')
				mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
					map->img.empty, j * 50, i * 50);
			print_map2(map, i, j, player);
			j++;
		}
		i++;
	}
}

int	ft_close(void)
{
	exit(1);
	return (0);
}
