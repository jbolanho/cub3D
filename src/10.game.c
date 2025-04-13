/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:50:08 by jbolanho          #+#    #+#             */
/*   Updated: 2025/04/12 17:32:56 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	game(t_game *cub)
{
	mlx_key_hook(cub->mlx, key_data, cub);
	mlx_loop_hook(cub->mlx, player_pov, cub);
	mlx_close_hook(cub->mlx, close_cub, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	return (EXIT_SUCCESS);
}

void	player_pov(void *param)
{
	t_game	*cub;

	cub = (t_game *)param;
	frame_speed(cub);
	take_input(cub);
	init_background(cub);
	dda(cub);
	mlx_image_to_window(cub->mlx, cub->image, 0, 0);
}

void	init_background(t_game *cub)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
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

void	frame_speed(t_game *cub)
{
	static mlx_image_t	*image;
	char				*fps_text;
	char				*fps_nbr;
	double				fps;

	cub->frame_time = cub->mlx->delta_time;
	if (cub->frame_time > 0)
		fps = 1.0 / cub->frame_time;
	else
		fps = 0;
	if (image)
		mlx_delete_image(cub->mlx, image);
	fps_nbr = ft_itoa((int)fps);
	fps_text = ft_strjoin("FPS:", fps_nbr);
	free(fps_nbr);
	image = mlx_put_string(cub->mlx, fps_text, WIDTH - 80, HEIGHT - 790);
	free(fps_text);
	cub->move_speed = cub->frame_time * 5.0;
	cub->rotation_speed = cub->frame_time * 3.0;
}
