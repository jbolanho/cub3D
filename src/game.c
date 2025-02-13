/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:52:56 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/13 17:33:05 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	game(t_game *cub)
{
	init_game(cub);
	init_images(cub);
	init_window(cub);
	mlx_loop_hook(cub->mlx, key_press, cub);
	mlx_loop()
}

void	init_game(t_game *cub)
{
	cub->window_wid = 800;
	cub->window_hei = 600;
	cub->mlx = mlx_init(cub->window_wid, cub->window_hei, "Severance", false);
	if (!cub->mlx)
	{
		ft_printf("Error. MLX init error.\n");
		bye_bye(cub, 1);
	}
	cub->time = mlx_get_time();
	//cub->rotation_speed = 0.02;
	// cub->move_speed = 0.06;
}

void	init_images(t_game *cub)
{
	//int	i;

	cub->no = mlx_load_png(cub->map.north_path);
	cub->so = mlx_load_png(cub->map.north_path);
	cub->ea = mlx_load_png(cub->map.north_path);
	cub->we = mlx_load_png(cub->map.north_path);

}

void	init_window(t_game *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	cub->floor_ceiling = mlx_new_image(cub->mlx, cub->window_wid, cub->window_hei);
	if (!cub->floor_ceiling)
	{
		ft_printf("Error. Floor Ceiling problem\n");
		bye_bye(cub);
	}
	while (x < cub->window_hei)
	{
		while (y < cub->window_wid)
		{
			if (x < (cub->window_hei / 2))
				mlx_put_pixel(cub->floor_ceiling, x, y, cub->map.ceiling_color);
			else
				mlx_put_pixel(cub->floor_ceiling, x, cub->map.floor_color);
			y++;
		}
		y = 0;
		x++;
	}
	mlx_image_to_window(cub->mlx)
}

void	key_press(t_game *cub)
{
	
}
