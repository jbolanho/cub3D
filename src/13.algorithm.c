/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13.algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:24:48 by jbolanho          #+#    #+#             */
/*   Updated: 2025/04/13 19:44:23 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	dda(t_game *cub)
{
	int		pixel_x;
	double	camera_x;

	pixel_x = 0;
	while (pixel_x < WIDTH)
	{
		camera_x = 2 * pixel_x / (float)WIDTH - 1;
		cub->ray.dir.x = cub->direction.x + cub->camera_plane.x * camera_x;
		cub->ray.dir.y = cub->direction.y + cub->camera_plane.y * camera_x;
		cub->ray.map.x = (int)cub->position.x;
		cub->ray.map.y = (int)cub->position.y;
		delta_dist(cub);
		cub->ray.hit_wall = 0;
		cub->ray.side = -1;
		step_and_side_distance(cub);
		perform_dda(cub);
		pixel_wall(cub, pixel_x);
		pixel_x++;
	}
}

void	delta_dist(t_game *cub)
{
	if (cub->ray.dir.x == 0)
		cub->ray.delta_dist.x = 1e30;
	else
		cub->ray.delta_dist.x = fabs(1 / cub->ray.dir.x);
	if (cub->ray.dir.y == 0)
		cub->ray.delta_dist.y = 1e30;
	else
		cub->ray.delta_dist.y = fabs(1 / cub->ray.dir.y);
}

void	step_and_side_distance(t_game *cub)
{
	if (cub->ray.dir.x < 0)
	{
		cub->ray.step.x = -1;
		cub->ray.side_dist.x = (cub->position.x - cub->ray.map.x)
			* cub->ray.delta_dist.x;
	}
	else
	{
		cub->ray.step.x = 1;
		cub->ray.side_dist.x = (cub->ray.map.x + 1.0 - cub->position.x)
			* cub->ray.delta_dist.x;
	}
	if (cub->ray.dir.y < 0)
	{
		cub->ray.step.y = -1;
		cub->ray.side_dist.y = (cub->position.y - cub->ray.map.y)
			* cub->ray.delta_dist.y;
	}
	else
	{
		cub->ray.step.y = 1;
		cub->ray.side_dist.y = (cub->ray.map.y + 1.0 - cub->position.y)
			* cub->ray.delta_dist.y;
	}
}

void	perform_dda(t_game *cub)
{
	while (cub->ray.map.x >= 0 && cub->ray.map.y >= 0 && (int) cub->ray.map.x < WIDTH
		&& (int) cub->ray.map.y < HEIGHT
		&& cub->map.cub_map[(int)cub->ray.map.y][(int)cub->ray.map.x] != '1')
	{
		if (cub->ray.side_dist.x < cub->ray.side_dist.y)
		{
			cub->ray.side_dist.x += cub->ray.delta_dist.x;
			cub->ray.map.x += cub->ray.step.x;
			cub->ray.hit_wall = 0;
		}
		else
		{
			cub->ray.side_dist.y += cub->ray.delta_dist.y;
			cub->ray.map.y += cub->ray.step.y;
			cub->ray.hit_wall = 1;
		}
	}
	if (cub->ray.hit_wall == 0)
		cub->ray.perp_dist = cub->ray.side_dist.x - cub->ray.delta_dist.x;
	else
		cub->ray.perp_dist = cub->ray.side_dist.y - cub->ray.delta_dist.y;
	if (cub->ray.perp_dist < 0.01f)
		cub->ray.perp_dist = 0.01f;
}

void	pixel_wall(t_game *cub, int pixel)
{
	cub->walls = get_wall(cub);
	cub->tex.height = (HEIGHT / cub->ray.perp_dist);
	cub->tex.start_y = (HEIGHT / 2 - cub->tex.height / 2);
	cub->tex.end_y = (HEIGHT / 2 + cub->tex.height / 2);
	if (cub->tex.start_y < 0)
		cub->tex.start_y = 0;
	if (cub->tex.end_y >= HEIGHT)
		cub->tex.end_y = HEIGHT - 1;
	wall_and_background(cub);
	find_pixel_wall(cub);
	if (cub->tex.texture_pos < 0)
		cub->tex.texture_pos = 0;
	put_pixel(cub, pixel);
}
