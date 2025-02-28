/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:24:48 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/11 12:35:47 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	algorithm(t_game *cub)
{
    int	i;

    i = -1;
    if (cub->walls)
        mlx_delete_image(cub->mlx, cub->walls);
    cub->walls = mlx_new_image(cub->mlx, cub->window_wid, cub->window_hei);
    if (!cub->walls)
    {
        printf("Error. Walls don't work");
        //bye_bye(cub, );
    }
    while (i < (int)cub->window_wid)
    {
        init_ray_struct(cub, i);
		delta_dist(cub);
		calculate_side_distance(cub);
		wall_distance(cub);
		
    }
	mlx_image_to_window(cub->mlx, cub->walls, 0, 0);
}

void	init_ray_struct(t_game *cub, int i)
{
	cub->ray.collide = false;
	cub->ray.camera_x = 2 * i / (double)cub->window_wid - 1;
	cub->ray.map_x = cub->map.p1_x;
	cub->ray.map_y = cub->map.p1_y;
	cub->ray.dir_x = cub->direction_x + cub->camera_plane_x * cub->ray.camera_x;
	cub->ray.dir_y = cub->direction_y + cub->camera_plane_y * cub->ray.camera_x;
}

void	delta_dist(t_game *cub)
{
	if (cub->ray.dir_x == 0)
		cub->ray.delta_dist_x = 1e30;
	else
		cub->ray.delta_dist_x = fabs(1 / cub->ray.dir_x);
	if (cub->ray.dir_y == 0)
		cub->ray.delta_dist_y = 1e30;
	else
		cub->ray.delta_dist_y = fabs(1 / cub->ray.dir_y);
}

void	calculate_side_distance(t_game *cub)
{
	if (cub->ray.dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.side_dist_x = (cub->map.p1_x - cub->ray.map_x)	* cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->map.p1_x) * cub->ray.delta_dist_x;
	}
	if (cub->ray.dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = (cub->map.p1_y - cub->ray.map_y)	* cub->ray.delta_dist_y;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->map.p1_y) * cub->ray.delta_dist_y;
	}
}

void	wall_distance(t_game *cub)
{
	while (!cub->ray.collide)
	{
		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
		{
			cub->ray.side_dist_x += cub->ray.delta_dist_x;
			cub->ray.map_x += cub->ray.step_x;
			wall_side(cub, X);
		}
		else
		{
			cub->ray.side_dist_y += cub->ray.delta_dist_y;
			cub->ray.map_y += cub->ray.step_y;
			wall_side(cub, Y);
		}
		if (cub->map_matrix[(int)cub->ray.map_y][(int)cub->ray.map_x] == '1'
			|| cub->map_matrix[(int)cub->ray.map_y][(int)cub->ray.map_x] == '2')
			cub->ray.collide = true;
	}
	if (cub->ray.side == EA || cub->ray.side == WE)
		cub->ray.perp_wall_dist = cub->ray.side_dist_x - cub->ray.delta_dist_x;
	else
		cub->ray.perp_wall_dist = cub->ray.side_dist_y - cub->ray.delta_dist_y;
}

void	wall_side(t_game *cub, int axis)
{
	if (axis == X && cub->ray.dir_x > 0)
		cub->ray.side = EA;
	if (axis == X && cub->ray.dir_x <= 0)
		cub->ray.side = WE;
	if (axis == Y && cub->ray.dir_y > 0)
		cub->ray.side = SO;
	if (axis == Y && cub->ray.dir_y <= 0)
		cub->ray.side = NO;
}

