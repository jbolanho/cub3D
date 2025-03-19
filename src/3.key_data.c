/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.key_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:50:29 by jbolanho          #+#    #+#             */
/*   Updated: 2025/03/19 15:00:01 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	key_data(mlx_key_data_t pressed, void *param)
{
	t_game	*cub;

	cub = (t_game *)param;
	if (pressed.key == MLX_KEY_ESCAPE && pressed.action == MLX_PRESS)
	{
		bye_bye(cub);
		mlx_close_window(cub->mlx);
		return ;
	}
	if (pressed.action == MLX_PRESS || pressed.action == MLX_REPEAT)
	{
		if (pressed.key == MLX_KEY_W)
			cub->key.w = true;
		if (pressed.key == MLX_KEY_S)
			cub->key.s = true;
		if (pressed.key == MLX_KEY_A)
			cub->key.a = true;
		if (pressed.key == MLX_KEY_D)
			cub->key.d = true;
		if (pressed.key == MLX_KEY_LEFT)
			cub->key.left = true;
		if (pressed.key == MLX_KEY_RIGHT)
			cub->key.right = true;
	}
	else if (pressed.action == MLX_RELEASE)
	{
		if (pressed.key == MLX_KEY_W)
			cub->key.w = false;
		if (pressed.key == MLX_KEY_S)
			cub->key.s = false;
		if (pressed.key == MLX_KEY_A)
			cub->key.a = false;
		if (pressed.key == MLX_KEY_D)
			cub->key.d = false;
		if (pressed.key == MLX_KEY_LEFT)
			cub->key.left = false;
		if (pressed.key == MLX_KEY_RIGHT)
			cub->key.right = false;
	}
}


void	take_input(t_game *cub)
{
	// cub->move_speed = cub->mlx->delta_time * 6;
	cub->move_speed = 0.06;
	if (cub->key.w == true)
		go_ahead(cub);
	if (cub->key.s == true)
		moon_walk(cub);
	if (cub->key.a == true)
		crab_walk(cub, MLX_KEY_A);
	if (cub->key.d == true)
		crab_walk(cub, MLX_KEY_D);
	look_movements(cub);
}

void	moon_walk(t_game *cub)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	x1 = (int)(cub->position.x - cub->direction.x * cub->move_speed);
	y1 = (int)cub->position.y;
	x2 = (int)cub->position.x;
	y2 = (int)(cub->position.y - cub->direction.y * cub->move_speed);
	if (cub->map.cub_map[y1][x1] != '1')
		cub->position.x -= cub->direction.x * cub->move_speed;
	if (cub->map.cub_map[y2][x2] != '1')
		cub->position.y -= cub->direction.y * cub->move_speed;
}

void	go_ahead(t_game *cub)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	x1 = (int)(cub->position.x + cub->direction.x * cub->move_speed);
	y1 = (int)cub->position.y;
	x2 = (int)cub->position.x;
	y2 = (int)(cub->position.y + cub->direction.y * cub->move_speed);
	if (cub->map.cub_map[y1][x1] != '1')
		cub->position.x += cub->direction.x * cub->move_speed;
	if (cub->map.cub_map[y2][x2] != '1')
		cub->position.y += cub->direction.y * cub->move_speed;
}

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
	if (key == MLX_KEY_A && (cub->map.cub_map[y1][x1] != '1' ))
	{
		cub->position.x += cub->direction.y * cub->move_speed;
		cub->position.y -= cub->direction.x * cub->move_speed;
	}
	if (key == MLX_KEY_D && (cub->map.cub_map[y2][x2] != '1'))
	{
		cub->position.x -= cub->direction.y * cub->move_speed;
		cub->position.y += cub->direction.x * cub->move_speed;
	}
}
