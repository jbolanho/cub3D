/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.initial_pov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:50:08 by jbolanho          #+#    #+#             */
/*   Updated: 2025/03/18 14:50:54 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	game(t_game *cub)
{
	mlx_key_hook(cub->mlx, key_data, cub);
	mlx_loop_hook(cub->mlx, player_pov, cub);
	mlx_close_hook(cub->mlx, close_cub, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
    // return(EXIT_SUCCESS);
}

void	player_pov(void *param)
{
	t_game	*cub;

	cub = (t_game *)param;
	take_input(cub);
	init_background(cub);
	frame_speed(cub);
	raycast(cub);
}

bool	can_go(t_game *cub, float x, float y)
{
	float	border;

	border = 0.1;
	if (cub->map.cub_map[(int)(y + border
			* minus_or_not(y - cub->position.y))][(int)x] == '1')
		return (false);
	if (cub->map.cub_map[(int)y][(int)(x + border
		* minus_or_not(x - cub->position.x))] == '1')
		return (false);
	if (cub->map.cub_map[(int)(y + border
			* minus_or_not(cub->camera_plane.y))][(int)x] == '1')
		return (false);
	if (cub->map.cub_map[(int)y][(int)(x + border
		* minus_or_not(cub->camera_plane.x))] == '1')
		return (false);
	return (true);
}

int	minus_or_not(float value)
{
	if (value < 0)
		return (-1);
	return (1);
}

void	look_movements(t_game *cub)
{
	if (cub->key.left == true)
	{
		cub->direction = rotate_vector(cub->direction, -1.5);
		cub->camera_plane = rotate_vector(cub->camera_plane, -1.5);
	}
	if (cub->key.right == true)
	{
		cub->direction = rotate_vector(cub->direction, 1.5);
		cub->camera_plane = rotate_vector(cub->camera_plane, 1.5);
	}
}

t_vector	rotate_vector(t_vector v, float angle)
{
	t_vector	vector;
	float		radians;

	radians = angle * 3.14159265 / 180.0;
	vector.x = v.x * cos(radians) - v.y * sin(radians);
	vector.y = v.x * sin(radians) + v.y * cos(radians);
	return (vector);
}

void	init_background(t_game *cub)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	// printf("color ceil: %d\n", cub->map.ceiling_color);
	// printf("color floor: %d\n", cub->map.floor_color);
	while (x < (uint32_t)HEIGHT)
	{
		while (y < (uint32_t)WIDTH)
		{
			if (x < (uint32_t)(HEIGHT / 2))
				mlx_put_pixel(cub->image, y, x, cub->map.ceiling_color);
			else
				mlx_put_pixel(cub->image, y, x, cub->map.floor_color);
			y++;
		}
		y = 0;
		x++;
	}
}
