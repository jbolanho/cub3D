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

#include <stdio.h>
//para apagar
static uint32_t create_color (uint32_t op, uint32_t r, uint32_t g, uint32_t b)
{
	return ((op << 24) | (r << 16) | (g << 8) | b);
}

static void fake_data(t_game *cub)
{
	//cub_map;
	uint32_t	nb_floor;
	uint32_t	nb_ceil;

	nb_floor = create_color(255, 169, 169, 169);
	nb_ceil = create_color(255, 250, 235, 215);
	printf("floor: %d\n", nb_floor);
	printf("ceiling: %d\n", nb_ceil);
	cub->map.north_path = "./texture/door1.png";
	cub->map.south_path = "./texture/door2.png";
	cub->map.east_path = "./texture/clock.png";
	cub->map.west_path = "./texture/wall.png";
	cub->map.floor_color = nb_floor;
	cub->map.ceiling_color = nb_ceil;
}

void	game(t_game *cub)
{
	fake_data(cub);
	init_game(cub);
	init_images(cub);
	init_window(cub);
	//mlx_loop_hook(cub->mlx, key_press, cub);
	//mlx_loop()
}

void	init_game(t_game *cub)
{
	cub->window_wid = 800;
	cub->window_hei = 600;
	cub->mlx = mlx_init(cub->window_wid, cub->window_hei, "Severance", false);
	if (!cub->mlx)
	{
		ft_printf("Error. MLX init error.\n");
		//bye_bye(cub, 1);
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
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	cub->floor_ceiling = mlx_new_image(cub->mlx, cub->window_wid, cub->window_hei);
	if (!cub->floor_ceiling)
	{
		ft_printf("Error. Floor Ceiling problem\n");
		//bye_bye(cub);
	}
	while (x < cub->window_hei)
	{
		while (y < cub->window_wid)
		{
			if (x < (cub->window_hei / 2))
				mlx_put_pixel(cub->floor_ceiling, x, y, cub->map.ceiling_color);
			else
				mlx_put_pixel(cub->floor_ceiling, x, y, cub->map.floor_color);
			y++;
		}
		y = 0;
		x++;
	}
	mlx_image_to_window(cub->mlx, cub->floor_ceiling, 0, 0);
	cub->floor_ceiling->instances->z = 0;
}

// void	key_press(t_game *cub)
// {
	
// }
