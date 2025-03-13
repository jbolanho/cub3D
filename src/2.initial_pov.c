
#include "../include/cub.h"

void	game(t_game *cub)
{
	// printf("AQUI  6 \n");
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
	// printf("AQUI  10 \n");
}

// void take_input(t_game *cub)
// {
// 	float   x;
//     float   y;
//     float   camera_mov;
//     float   move_speed;
	
//     x = cub->position.x;
//     y = cub->position.y;
//     camera_mov = 1;
//     move_speed = 0.02;
// 	// move_speed = cub->frame_time * 4;
// 	// printf("AQUI  7 \n");
//     // if  (mlx_is_key_down(cub->mlx, MLX_KEY_W))
// 	if (cub->key.w == true)
// 	{
// 		x += cub->direction.x * move_speed;
// 		y += cub->direction.y * move_speed;
// 	}
//     // if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
// 	if (cub->key.s == true)
// 	{
// 		x -= cub->direction.x * move_speed;
// 		y -= cub->direction.y * move_speed;
// 	}
// 	// if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
// 	if (cub->key.a == true)
// 	{
// 		x += cub->camera_plane.x * move_speed;
// 		y += cub->camera_plane.y * move_speed;
// 	}
// 	// if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
// 	if (cub->key.d == true)
// 	{
// 		x += cub->camera_plane.x * move_speed;
// 		y += cub->camera_plane.y * move_speed;
// 	}
// 	if(can_go(cub, x, y))
// 	{
// 		cub->position.x = cub->position.x + camera_mov * (x - cub->position.x);
// 		cub->position.y = cub->position.y + camera_mov * (y - cub->position.y);
// 	}
//     look_movements(cub);
// }

bool	can_go(t_game *cub, float x, float y)
{
	float	border;
	
	border = 0.1;
	if (cub->map.cub_map[(int)(y + border * minus_or_not(y - cub->position.y))][(int)x] == '1')
		return(false);
	if (cub->map.cub_map[(int)y][(int)(x + border * minus_or_not(x - cub->position.x))] == '1')
		return(false);
	if (cub->map.cub_map[(int)(y + border * minus_or_not(cub->camera_plane.y))][(int)x] == '1')
		return(false);
	if (cub->map.cub_map[(int)y][(int)(x + border * minus_or_not(cub->camera_plane.x))] == '1')
		return(false);
	// printf("AQUI  8 \n");
	return(true);
}
int	minus_or_not(float value)
{
	if (value < 0)
		return (-1);
	return (1);
}

void    look_movements(t_game *cub)
{
	// double	old_dir;
	// double	old_plane_x;

	// old_dir = cub->direction.x;
	// old_plane_x = cub->camera_plane.x;
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	if (cub->key.left == true)
	{
		cub->direction = rotate_vector(cub->direction, -1.5);
		cub->camera_plane = rotate_vector(cub->camera_plane, -1.5);
	}	
	
	if (cub->key.right == true)
	{
		cub->direction = rotate_vector(cub->direction, 1.5);
		cub->camera_plane =  rotate_vector(cub->camera_plane, 1.5);
	}
	// printf("AQUI  9 \n");
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
	// printf("AQUI  4 \n");
	// cub->floor_ceiling = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	// if (!cub->floor_ceiling)
	// {
	// 	ft_printf("Error. Floor Ceiling problem\n");
	// 	//bye_bye(cub);
	// }
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
	// printf("AQUI  4a \n");
	// mlx_image_to_window(cub->mlx, cub->floor_ceiling, 0, 0);
}