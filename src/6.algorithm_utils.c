/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.algorithm_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:24:55 by jbolanho          #+#    #+#             */
/*   Updated: 2025/04/03 15:09:29 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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
		cub->tex.point_x = cub->position.y + cub->ray.perp_dist
			* cub->ray.dir.y;
	else
		cub->tex.point_x = cub->position.x + cub->ray.perp_dist
			* cub->ray.dir.x;
	cub->tex.point_x -= floor(cub->tex.point_x);
}

void	find_pixel_wall(t_game *cub)
{
	cub->tex.texture_x = (int)(cub->tex.point_x * cub->walls->width);
	if ((cub->ray.hit_wall == 0 && cub->ray.dir.x < 0)
		|| (cub->ray.hit_wall == 1 && cub->ray.dir.y > 0))
		cub->tex.texture_x = cub->walls->width - cub->tex.texture_x - 1;
	cub->tex.texture_step = 1.0 * cub->walls->height / cub->tex.height;
	cub->tex.texture_pos = (cub->tex.start_y - HEIGHT / 2 + cub->tex.height / 2)
		* cub->tex.texture_step;
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
