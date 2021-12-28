/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 05:06:54 by kid-bouh          #+#    #+#             */
/*   Updated: 2021/12/28 16:11:18 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_putstr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		write(1,&str[i],1);
		i++;
	}
}

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
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	while((line = get_next_line(fd)))
	{
		if(!width)
			width = ft_strlen_nl(line);
		if(width != ft_strlen_nl(line))
			ft_error();
		height++;
	}
	map->height = height;
	map->width = width;
}

void	p_map(char *file, t_map *map)
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
}

void *init_image(char *file, t_mlx *mlx)
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

void init_images(t_mlx *mlx, t_img *img)
{
	img->empty = init_image("img/empty.xpm", mlx);
	img->collect = init_image("img/collect2.xpm", mlx);
	img->wall = init_image("img/wall.xpm", mlx);
	img->player = init_image("img/player2.xpm", mlx);
	img->exit0 = init_image("img/door_close.xpm", mlx);
	img->exit1 = init_image("img/door_open.xpm", mlx);
}

void print_map(t_mlx *mlx, t_map *map, t_img *img)
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
				mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, img->wall, j * 50, i * 50);
			if (map->map[i][j] == '0' || map->map[i][j] == 'E' || map->map[i][j] == 'P')
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img->empty, j * 50, i * 50);
			if (map->map[i][j] == 'P')
			{
				map->x = i;
				map->y = j;
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img->player, j * 50, i * 50);
			}
			if(map->map[i][j] == 'E')
			{
				map->x_exit = i;
				map->y_exit = j;
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img->exit0, j * 50, i * 50);
			}
			if (map->map[i][j] == 'C')
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img->collect, j * 50, i * 50);
			j++;
		}
		i++;
	}
}

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

int main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx;
	t_img	img;
	
	p_map("maps/map2.ber", &map);
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, (map.width * 50), (map.height * 50), "so_long");
	init_images(&mlx, &img);
	map.mlx = mlx;
	map.img = img;
	print_map(&mlx, &map, &img);
	map.mlx = mlx;
	map.img = img;
	map.count_move = 0;
	mlx_hook(mlx.win, 2, 0, &key_press, &map);
	mlx_loop(mlx.mlx_ptr);
}