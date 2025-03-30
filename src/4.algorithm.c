/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.algorithm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:24:48 by jbolanho          #+#    #+#             */
/*   Updated: 2025/03/24 15:20:14 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// void	dda(t_game *cub)
// {
// 	int	pixel_x;

// 	pixel_x = 0;
// 	while (pixel_x < WIDTH)
// 	{
// 		cub->ray.plane_multi = 2 * pixel_x / (float)WIDTH - 1;
// 		cub->ray.camera_pixel.x = cub->camera_plane.x * cub->ray.plane_multi;
// 		cub->ray.camera_pixel.y = cub->camera_plane.y * cub->ray.plane_multi;
// 		cub->ray.direction.x = cub->direction.x + cub->ray.camera_pixel.x;
// 		cub->ray.direction.y = cub->direction.y + cub->ray.camera_pixel.y;
// 		cub->ray.step.x = minus_or_not(cub->ray.direction.x);
// 		cub->ray.step.y = minus_or_not(cub->ray.direction.y);
// 		delta_dist(cub);
// 		wall_dist(cub);
// 		not_collide(cub);
// 		pixel_wall(cub, pixel_x);
// 		pixel_x++;
// 	}
// }
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
		cub->ray.map.x = cub->position.x;
		cub->ray.map.y = cub->position.y;
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
		cub->ray.side_dist.x = (cub->position.x - cub->ray.map.x) * cub->ray.delta_dist.x;
	}
	else
	{
		cub->ray.step.x = 1;
		cub->ray.side_dist.x = (cub->ray.map.x + 1.0 - cub->position.x)	* cub->ray.delta_dist.x;
	}
	if (cub->ray.dir.y < 0)
	{
		cub->ray.step.y = -1;
		cub->ray.side_dist.y = (cub->position.y - cub->ray.map.y) * cub->ray.delta_dist.y;
	}
	else
	{
		cub->ray.step.y = 1;
		cub->ray.side_dist.y = (cub->ray.map.y + 1.0 - cub->position.y)	* cub->ray.delta_dist.y;
	}
}

// void	perform_dda(t_game *cub)
// {
// 	// while (cub->ray.map.x >= 0 && cub->ray.map.y >= 0 && cub->ray.map.x < WIDTH && cub->ray.map.y < HEIGHT && cub->map.cub_map[(int)cub->ray.map.y][(int)cub->ray.map.x] != '1')
// 	// while (cub->map.cub_map[(int)cub->ray.map.y][(int)cub->ray.map.x] != '1')
// 	while (cub->ray.hit_wall == 0)
// 	{
// 		if (cub->ray.side_dist.x < cub->ray.side_dist.y)
// 		{
// 			cub->ray.side_dist.x += cub->ray.delta_dist.x;
// 			cub->ray.map.x += cub->ray.step.x;
// 			cub->ray.side = 0;
// 		}
// 		else
// 		{
// 			cub->ray.side_dist.y += cub->ray.delta_dist.y;
// 			cub->ray.map.y += cub->ray.step.y;
// 			cub->ray.side = 1;
// 		}
// 		if (cub->map.cub_map[(int)cub->ray.map.y][(int)cub->ray.map.x] == '1')
// 			cub->ray.hit_wall = 1;
// 	}
// 	if (cub->ray.side == 0)
// 		cub->ray.perp_dist = cub->ray.side_dist.x - cub->ray.delta_dist.x;
// 	else
// 		cub->ray.perp_dist = cub->ray.side_dist.y - cub->ray.delta_dist.y;
// }

// void	pixel_wall(t_game *cub, int pixel)
// {
// 	cub->tex.height = (HEIGHT / cub->ray.perp_dist);
// 	cub->tex.start_y = ((- cub->tex.height / 2) + (HEIGHT / 2));
// 	if (cub->tex.start_y < 0)
// 		cub->tex.start_y = 0;
// 	cub->tex.end_y = ((cub->tex.height / 2) + (HEIGHT / 2));
// 	if (cub->tex.end_y >= HEIGHT)
// 		cub->tex.end_y = HEIGHT - 1;
// 	cub->walls = get_wall(cub);
// 	wall_x_value(cub);
// 	find_pixel_wall(cub);
// 	put_pixel(cub, pixel);
// }

// mlx_texture_t	*get_wall(t_game *cub)
// {
// 	if (cub->ray.side == 1)
// 	{
// 		if (cub->ray.step.y < 0)
// 			return (cub->no);
// 		else
// 			return (cub->so);
// 	}
// 	else
// 	{
// 		if (cub->ray.step.x < 0)
// 			return (cub->we);
// 		else
// 			return (cub->ea);
// 	}
// 	return (NULL);
// }

// void	wall_x_value(t_game *cub)
// {
// 	if (cub->ray.side == 0)
// 		cub->tex.wall_x = cub->position.y + cub->ray.perp_dist * cub->ray.dir.y;
// 	else
// 		cub->tex.wall_x = cub->position.x + cub->ray.perp_dist * cub->ray.dir.x;
// 	cub->tex.wall_x -= floor(cub->tex.wall_x);
// 	cub->tex.tex_x = (int)cub->tex.wall_x * cub->walls->width;
// 	// if(cub->ray.side == 0 && cub->ray.dir.x > 0)
// 	// 	cub->tex.tex_x = cub->walls->width - cub->tex.tex_x - 1;
// 	// if(cub->ray.side == 1 && cub->ray.dir.x < 0)
// 	// 	cub->tex.tex_x = cub->walls->width - cub->tex.tex_x - 1;
// }

// void	find_pixel_wall(t_game *cub)
// {
// 	cub->tex.texture_step = 1.0 * cub->walls->height / cub->tex.height;
// 	cub->tex.texture_pos = (cub->tex.start_y - HEIGHT / 2 + cub->tex.height / 2) * cub->tex.texture_step;
// 	if (cub->tex.texture_pos < 0)
//     	cub->tex.texture_pos = 0;
// }

// void	put_pixel(t_game *cub, int pixel)
// {
// 	int			y;
// 	int			wall_y;
// 	uint32_t	color;

// 	y = cub->tex.start_y;
// 	while (y < cub->tex.end_y)
// 	{
// 		wall_y = (int)cub->tex.texture_pos;
// 		// if (wall_y < 0)
// 		// 	wall_y = 0;
// 		if (wall_y >= (int)cub->walls->height)
// 			wall_y = cub->walls->height - 1;
// 		cub->tex.texture_pos += cub->tex.texture_step;
// 		color = get_color(cub->walls, wall_y, cub->tex.tex_x);
// 		mlx_put_pixel(cub->image, pixel, y, color);
// 		y++;
// 	}
// }

// uint32_t	get_color(mlx_texture_t	*walls, int y, int x)
// {
// 	int		pos;
// 	uint8_t	*pixel;

// 	if (x < 0 || x >= (int)walls->width || y < 0 || y >= (int)walls->height)
// 		return (0);
// 	pos = y * walls->width + x;
// 	pos *= walls->bytes_per_pixel;
// 	pixel = &walls->pixels[pos];
// 	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
// }





void	perform_dda(t_game *cub)
{
	while (cub->ray.map.x >= 0 && cub->ray.map.y >= 0 && cub->ray.map.x < WIDTH && cub->ray.map.y < HEIGHT && cub->map.cub_map[(int)cub->ray.map.y][(int)cub->ray.map.x] != '1')
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
	// cub->tex.texture_pos = (cub->tex.start_y - HEIGHT / 2 + cub->tex.height / 2) * cub->tex.texture_step;
	if (cub->tex.texture_pos < 0)
    	cub->tex.texture_pos = 0;
	put_pixel(cub, pixel);
}

mlx_texture_t	*get_wall(t_game *cub)
{
	if (cub->ray.hit_wall == 1)
	{
		if (cub->ray.step.y < 0)
			return (cub->no);
		else
			return (cub->so);
	}
	else
	{
		if (cub->ray.step.x < 0)
			return (cub->we);
		else
			return (cub->ea);
	}
	return (NULL);
}

void	wall_and_background(t_game *cub)
{
	if (cub->ray.hit_wall == 0)
		cub->tex.point_x = cub->position.y + cub->ray.perp_dist * cub->ray.dir.y;
	else
		cub->tex.point_x = cub->position.x + cub->ray.perp_dist * cub->ray.dir.x;
	cub->tex.point_x -= floor(cub->tex.point_x);
}

void	find_pixel_wall(t_game *cub)
{
	cub->tex.texture_x = (int)(cub->tex.point_x * cub->walls->width);
	if ((cub->ray.hit_wall == 0 && cub->ray.dir.x < 0)	|| (cub->ray.hit_wall == 1 && cub->ray.dir.y > 0))
		cub->tex.texture_x = cub->walls->width - cub->tex.texture_x - 1;
	cub->tex.texture_step = 1.0 * cub->walls->height / cub->tex.height;
	cub->tex.texture_pos = (cub->tex.start_y - HEIGHT / 2 + cub->tex.height / 2) * cub->tex.texture_step;
}

void	put_pixel(t_game *cub, int pixel)
{
	int			y;
	int			wall_y;
	uint32_t	color;

	y = cub->tex.start_y;
	while (y < cub->tex.end_y)
	{
		cub->tex.texture_pos += cub->tex.texture_step;
		wall_y = (int)cub->tex.texture_pos;
		// wall_y = (int)cub->tex.texture_pos;
		if (wall_y < 0)
			wall_y = 0;
		if (wall_y >= (int)cub->walls->height)
			wall_y = cub->walls->height - 1;
		color = get_color(cub->walls, wall_y, cub->tex.texture_x);
		mlx_put_pixel(cub->image, pixel, y, color);
		y++;
	}
}

uint32_t	get_color(mlx_texture_t	*walls, int y, int x)
{
	int		pos;
	uint8_t	*pixel;

	if (x < 0 || x >= (int)walls->width || y < 0 || y >= (int)walls->height)
		return (0);
	pos = y * walls->width + x;
	pos *= walls->bytes_per_pixel;
	pixel = &walls->pixels[pos];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}