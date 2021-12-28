/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 05:08:44 by kid-bouh          #+#    #+#             */
/*   Updated: 2021/12/28 16:04:19 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win;
}	t_mlx;

typedef struct s_img
{
	void	*wall;
	void	*player;
	void	*collect;
	void	*exit0;
	void	*exit1;
	void	*empty;
}	t_img;

typedef	struct s_map
{
	char	**map;
	int		width;
	int		height;
	t_img	img;
	t_mlx	mlx;
	int		x;
	int		y;
	int		count_move;
	int		x_exit;
	int		y_exit;
}	t_map;

#endif