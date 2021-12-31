/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 05:06:54 by kid-bouh          #+#    #+#             */
/*   Updated: 2021/12/31 20:31:55 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

void so_long(char *path)
{
	t_map	map;
	t_mlx	mlx;
	t_img	img;
	
	parsing_map(path, &map);
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, (map.width * 50), (map.height * 50), "so_long");
	init_images(&mlx, &img);
	print_map(&mlx, &map, &img);
	map.mlx = mlx;
	map.img = img;
	map.count_move = 0;
	mlx_hook(mlx.win, 2, 0, &key_press, &map);
	mlx_loop(mlx.mlx_ptr);
}

int	main(int ac, char **av)
{
	if(ac == 2)
	{
		so_long(av[1]);
	}
	else
	{
		ft_putstr("error syntaxe\n");
	}
}