/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12.key_data_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:52:56 by jbolanho          #+#    #+#             */
/*   Updated: 2025/04/14 16:46:20 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	crab_walk(t_game *cub, int key)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	x1 = (int)(cub->position.x + cub->direction.y * cub->move_speed);
	y1 = (int)(cub->position.y - cub->direction.x * cub->move_speed);
	x2 = (int)(cub->position.x - cub->direction.y * cub->move_speed);
	y2 = (int)(cub->position.y + cub->direction.x * cub->move_speed);
	if (key == MLX_KEY_A && y1 < cub->map.height && x1 < cub->map.width && cub->map.cub_map[y1][x1] && (cub->map.cub_map[y1][x1] != '1' ))
	{
		cub->position.x += cub->direction.y * cub->move_speed;
		cub->position.y -= cub->direction.x * cub->move_speed;
	}
	if (key == MLX_KEY_D && y2 < cub->map.height && x2 < cub->map.width && cub->map.cub_map[y2][x2] && (cub->map.cub_map[y2][x2] != '1'))
	{
		cub->position.x -= cub->direction.y * cub->move_speed;
		cub->position.y += cub->direction.x * cub->move_speed;
	}
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
