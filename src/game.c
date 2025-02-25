/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:52:56 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/13 17:33:05 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

//para apagar
static uint32_t create_color (uint32_t op, uint32_t r, uint32_t g, uint32_t b)
{
	uint32_t	nb;

	nb = (op << 24) | (r << 16) | (g << 8) | b;
	
	return (nb);
}

static void fake_data(t_game *cub)
{
	//cub_map;
	uint32_t	nb_floor;
	uint32_t	nb_ceil;

	nb_floor = create_color(255, 169, 169, 169);
	nb_ceil = create_color(255, 250, 235, 215);
	printf("floor: %u\n", nb_floor);
	printf("ceiling: %u\n", nb_ceil);
	cub->map.north_path = "./texture/door1.png";
	cub->map.south_path = "./texture/door2.png";
	cub->map.east_path = "./texture/clock.png";
	cub->map.west_path = "./texture/wall.png";
	cub->map.floor_color = nb_floor;
	cub->map.ceiling_color = nb_ceil;
	printf("AQUI  1 \n");
}

void	game(t_game *cub)
{
	fake_data(cub);
	init_game(cub);
	init_images(cub);
	init_window(cub);
	mlx_loop_hook(cub->mlx, key_press, cub);
	printf("AQUI  5 \n");
	mlx_loop(cub->mlx);
	printf("AQUI  6 \n");
	//mlx_terminate(cub->mlx);
}

void	init_game(t_game *cub)
{
	printf("AQUI  2 \n");
	cub->window_wid = 800;
	cub->window_hei = 600;
	cub->mlx = mlx_init((int32_t)cub->window_wid, (int32_t)cub->window_hei, "Severance", false);
	if (!cub->mlx)
	{
		ft_printf("Error. MLX init error.\n");
		//bye_bye(cub, 1);
	}
}

void	init_images(t_game *cub)
{
	//int	i;
	printf("AQUI  3 \n");
	cub->no = mlx_load_png(cub->map.north_path);
	cub->so = mlx_load_png(cub->map.south_path);
	cub->ea = mlx_load_png(cub->map.east_path);
	cub->we = mlx_load_png(cub->map.west_path);

}

void	init_window(t_game *cub)
{
	init_background(cub);
	//algorithm(cub);
	//bonus_minimap(cub);
}	

void	init_background(t_game *cub)
{	
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	printf("AQUI  4 \n");
	cub->floor_ceiling = mlx_new_image(cub->mlx, cub->window_wid, cub->window_hei);
	if (!cub->floor_ceiling)
	{
		ft_printf("Error. Floor Ceiling problem\n");
		//bye_bye(cub);
	}
	while (x < (uint32_t)cub->window_hei)
	{
		while (y < (uint32_t)cub->window_wid)
		{
			if (x < (uint32_t)(cub->window_hei / 2))
				mlx_put_pixel(cub->floor_ceiling, y, x, cub->map.ceiling_color);
			else
				mlx_put_pixel(cub->floor_ceiling, y, x, cub->map.floor_color);
			y++;
		}
		y = 0;
		x++;
	}
	mlx_image_to_window(cub->mlx, cub->floor_ceiling, 0, 0);
	cub->floor_ceiling->instances->z = 0;
}

void	key_press(void *param)
{
	t_game	*cub;

	cub = param;
	printf("AQUI  7 \n");
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		printf("aquiii3");
	//	bye_bye(cub, EXIT_SUCCESS);
	if  (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	// //|| (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN)
	 	moon_walk(cub);
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	// //|| (mlx_is_key_down(cub->mlx, MLX_KEY_UP)
	// 	go_ahead(cub);
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	// 	crab_walk(cub, MLX_KEY_A);
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	// 	crab_walk(cub, MLX_KEY_D);
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	// 	look_right(cub);
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	// 	look_left(cub);
	// // if (mlx_is_key_down(cub->mlx, MLX_KEY_SPACE))
	// // 	bonus_open_door(cub);
	// //update(cub);
	printf("AQUI  8 \n");
}

// void	update(t_game *cub)
// {
// 	//bonus_close_open_doors(cub);
// 	calculate_frames_per_second(cub);
// 	raycast(cub);
// 	//bonus_draw_minimap(cub);
// }

