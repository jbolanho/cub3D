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

void    raycast(t_game *cub)
{
    int     pixel;

    pixel = 0;
	// printf("AQUI  11 \n");
    while (pixel < WIDTH)
    {
        cub->ray.plane_multi = 2 * pixel / (float)WIDTH - 1;
        cub->ray.camera_pixel.x = cub->camera_plane.x *  cub->ray.plane_multi;
        cub->ray.camera_pixel.y = cub->camera_plane.y *  cub->ray.plane_multi;
        cub->ray.direction.x = cub->direction.x +  cub->ray.camera_pixel.x;
        cub->ray.direction.y = cub->direction.y +  cub->ray.camera_pixel.y;
        cub->ray.step.x = minus_or_not(cub->ray.direction.x);
        cub->ray.step.y = minus_or_not(cub->ray.direction.y);
        delta_dist(cub);
        wall_dist(cub);
        not_collide(cub);
        pixel_wall(cub, pixel);
        pixel++;
    }
	// mlx_image_to_window(cub->mlx, cub->floor_ceiling, 0, 0);
	// printf("AQUI  12 \n");
}

void	delta_dist(t_game *cub)
{
	if (cub->ray.direction.x == 0)
		cub->ray.delta_dist.x = 1e30;
	else
		cub->ray.delta_dist.x = fabs(1 / cub->ray.direction.x);
	if (cub->ray.direction.y == 0)
		cub->ray.delta_dist.y = 1e30;
	else
		cub->ray.delta_dist.y = fabs(1 / cub->ray.direction.y);
}

void    wall_dist(t_game *cub)
{
	cub->ray.map.x = cub->map.p1_x;
	cub->ray.map.y = cub->map.p1_y;
	if(cub->ray.direction.x < 0)
		cub->ray.side_dist.x = (cub->position.x - cub->ray.map.x) * cub->ray.delta_dist.x;
	else
		cub->ray.side_dist.x = (cub->ray.map.x + 1 - cub->position.x) * cub->ray.delta_dist.x;
	if(cub->ray.direction.y < 0)
		cub->ray.side_dist.y = (cub->position.y - cub->ray.map.y) * cub->ray.delta_dist.y;
	else
		cub->ray.side_dist.y = (cub->ray.map.y + 1 - cub->position.y) * cub->ray.delta_dist.y;
}   

void	not_collide(t_game *cub)
{
	while(cub->map.cub_map[(int)cub->ray.map.y][(int)cub->ray.map.x] != '1')
	{
		if (cub->ray.side_dist.x < cub->ray.side_dist.y)
		{
			cub->ray.side_dist.x += cub->ray.delta_dist.x;
			cub->ray.map.x += cub->ray.step.x;
			cub->ray.collide = 0;
			cub->collide = 0;                                             //
		}
		else
		{
			cub->ray.side_dist.y += cub->ray.delta_dist.y;
			cub->ray.map.y += cub->ray.step.y;
			cub->ray.collide = 1;
			cub->collide = 1;
		}
	}
	if (cub->ray.collide == 0)
		cub->ray.perp_dist = cub->ray.side_dist.x - cub->ray.delta_dist.x;
	else
		cub->ray.perp_dist = cub->ray.side_dist.y - cub->ray.delta_dist.y;
}

void	pixel_wall(t_game *cub, int pixel)
{
	cub->walls = get_wall(cub);
	cub->tex.height = (HEIGHT / cub->ray.perp_dist);
	cub->tex.start_y = (HEIGHT / 2 - cub->tex.height / 2);
	cub->tex.end_y = (HEIGHT / 2 + cub->tex.height / 2);
	if (cub->tex.start_y < 0)
		cub->tex.start_y = 0;
	if (cub->tex.end_y > HEIGHT)
		cub->tex.end_y = HEIGHT;
	wall_and_background(cub);
	find_pixel_wall(cub);
	cub->tex.texture_pos = (cub->tex.start_y - HEIGHT / 2 + cub->tex.height / 2) * cub->tex.texture_step;
	put_pixel(cub, pixel);
}

mlx_texture_t	*get_wall(t_game *cub)
{
	if(cub->collide == 1)
	{
		if(cub->ray.step.y < 0)
			return(cub->no);
		else 
			return(cub->so);
	}
	else
	{
		if (cub->ray.step.x < 0)
			return(cub->we);
		else
			return(cub->ea);
	}
	return (NULL);
}

void	wall_and_background(t_game *cub)
{
	if (cub->collide == 0)
		cub->tex.point_x = cub->position.y + cub->ray.perp_dist * cub->ray.direction.y;
	else
		cub->tex.point_x = cub->position.x + cub->ray.perp_dist * cub->ray.direction.x;
	cub->tex.point_x -= floor(cub->tex.point_x);
}

void	find_pixel_wall(t_game *cub)
{
	cub->tex.texture_x = (int)(cub->tex.point_x * cub->walls->width);
	if((cub->collide == 0 && cub->ray.direction.x < 0) || (cub->collide == 1 && cub->ray.direction.y > 0))
		cub->tex.texture_x = cub->walls->width - cub->tex. texture_x - 1;
	cub->tex.texture_step = 1 * cub->walls->height / cub->tex.height;
}

void	put_pixel(t_game *cub, int pixel)
{
	int			y;
	int			wall_y;
	uint32_t	color;

	y = cub->tex.start_y;
	while(y < cub->tex.end_y)
	{
		wall_y = (int)cub->tex.texture_pos;
		if (wall_y < 0)
			wall_y = 0;
		if (wall_y >= (int)cub->walls->height)
			wall_y = cub->walls->height - 1;
		cub->tex.texture_pos += cub->tex.texture_step;
		color = get_color(cub->walls, wall_y, cub->tex.texture_x);
		mlx_put_pixel(cub->floor_ceiling, pixel, y, color);
		y++;
	}
}

uint32_t	get_color(mlx_texture_t	*walls, int y, int x)
{
	int		pos;
	uint8_t	*pixel;

	if(x < 0 || x >= (int)walls->width || y < 0 || y >= (int)walls->height)
		return (0);
	pos = y * walls->width + x;
	pos *= walls->bytes_per_pixel;
	pixel = &walls->pixels[pos];
	// printf("R: %d, G: %d, B: %d, A: %d\n", pixel[0], pixel[1], pixel[2], pixel[3]);
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}