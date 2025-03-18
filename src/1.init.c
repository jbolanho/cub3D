/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:24:55 by jbolanho          #+#    #+#             */
/*   Updated: 2025/03/18 10:50:20 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	get_rgba(int r, int g, int b, int a);
static void	fake_data(t_game *cub);

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	fake_data(t_game *cub)
{
	uint32_t	nb_floor;
	uint32_t	nb_ceil;

	nb_floor = get_rgba(169, 169, 169, 255);
	nb_ceil = get_rgba(230, 230, 230, 255);
	cub->map.north_path = "./texture/door1.png";
	cub->map.south_path = "./texture/door2.png";
	cub->map.east_path = "./texture/clock.png";
	cub->map.west_path = "./texture/wall.png";
	cub->map.floor_color = nb_floor;
	cub->map.ceiling_color = nb_ceil;
	cub->map.p1_x = 5;
	cub->map.p1_y = 4;
	cub->map.p1_pov = S;
	copy_map(cub);
}

void	init(t_game *cub)
{
	fake_data(cub);
	init_window(cub);
	init_images(cub);
	initial_pov(cub);
}

void	init_window(t_game *cub)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cub->mlx = mlx_init((int32_t)WIDTH, (int32_t)HEIGHT, "Severance", true);
	if (!cub->mlx)
	{
		ft_printf("Error. MLX init error.\n");
		bye_bye(cub);
	}
	cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image)
	{
		ft_printf("Error. Window problem\n");
		bye_bye(cub);
	}
	if (mlx_image_to_window(cub->mlx, cub->image, 0, 0) < 0)
	{
		ft_printf("Error. Image problem\n");
		bye_bye(cub);
	}
}

void	init_images(t_game *cub)
{
	cub->no = mlx_load_png(cub->map.north_path);
	cub->so = mlx_load_png(cub->map.south_path);
	cub->ea = mlx_load_png(cub->map.east_path);
	cub->we = mlx_load_png(cub->map.west_path);
}

void	initial_pov(t_game *cub)
{
	cub->position = vector(cub->map.p1_x + 0.5, cub->map.p1_y + 0.5);
	if (cub->map.p1_pov == N)
	{
		cub->direction = vector(0, -1);
		cub->camera_plane = vector(0.66, 0);
	}
	else if (cub->map.p1_pov == S)
	{
		cub->direction = vector(0, 1);
		cub->camera_plane = vector(-0.66, 0);
	}
	else if (cub->map.p1_pov == W)
	{
		cub->direction = vector(-1, 0);
		cub->camera_plane = vector(0, -0.66);
	}
	else if (cub->map.p1_pov == E)
	{
		cub->direction = vector(1, 0);
		cub->camera_plane = vector(0, 0.66);
	}
}

t_vector	vector(float x, float y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}
