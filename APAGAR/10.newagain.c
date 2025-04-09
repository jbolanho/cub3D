#include "../include/cub.h"
// AQUII

void	init(t_game *cub)
{
	// fake_data(cub);
	initial_pov(cub);
	init_window(cub);
	init_images(cub);
	// init_time(cub);
	// init_background(cub);
	// dda(cub);
	// mlx_image_to_window(cub->mlx, cub->image, 0, 0);
}

void	init_window(t_game *cub)
{
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cub->mlx = mlx_init((int32_t)WIDTH, (int32_t)HEIGHT, "Severance", true);
	if (!cub->mlx)
	{
		ft_printf("Error. MLX init error.\n");
		bye_bye(cub);
	}
	cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image)
	{
		ft_printf("Error. Window problem\n");
		bye_bye(cub);
	}
	if (mlx_image_to_window(cub->mlx, cub->image, 0, 0) < 0)
	{
		ft_printf("Error. Image problem\n");
		bye_bye(cub);
	}
}

void	init_images(t_game *cub)
{
	cub->no = mlx_load_png(cub->map.north_path);
	cub->so = mlx_load_png(cub->map.south_path);
	cub->ea = mlx_load_png(cub->map.east_path);
	cub->we = mlx_load_png(cub->map.west_path);
}

void	initial_pov(t_game *cub)
{
	// printf("AQUII px: %d\n", cub->map.player_x);
	// printf("AQUII py: %d\n", cub->map.player_y);
	// printf("AQUII pov: %d\n", cub->map.player_pov);
	cub->position = vector(cub->map.player_x + 0.5, cub->map.player_y + 0.5);
	if (cub->map.player_pov == N)
	{
		cub->direction = vector(0, -1);
		cub->camera_plane = vector(0.66, 0);
	}
	else if (cub->map.player_pov == S)
	{
		cub->direction = vector(0, 1);
		cub->camera_plane = vector(-0.66, 0);
	}
	else if (cub->map.player_pov == W)
	{
		cub->direction = vector(-1, 0);
		cub->camera_plane = vector(0, -0.66);
	}
	else if (cub->map.player_pov == E)
	{
		cub->direction = vector(1, 0);
		cub->camera_plane = vector(0, 0.66);
	}
    
}

t_vector	vector(float x, float y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

int	game(t_game *cub)
{
	mlx_key_hook(cub->mlx, key_data, cub);
	mlx_loop_hook(cub->mlx, player_pov, cub);
	mlx_close_hook(cub->mlx, close_cub, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
    return(EXIT_SUCCESS);
}

void	player_pov(void *param)
{
	t_game	*cub;

	cub = (t_game *)param;
	// mlx_delete_image(cub->mlx, cub->image);
	// cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	frame_speed(cub);
	take_input(cub);
	init_background(cub);
	dda(cub);
	// mlx_image_to_window(cub->mlx, cub->image, 0, 0);
}

int	minus_or_not(float value)
{
	if (value < 0)
		return (-1);
	return (1);
}

void	init_background(t_game *cub)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	cub->floor_ceiling = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->map.ceiling_color = 2162219392;
	cub->map.floor_color = 2155905344;
	while (x < (uint32_t)HEIGHT)
	{
		while (y < (uint32_t)WIDTH)
		{
			if (x < (uint32_t)(HEIGHT / 2))
				mlx_put_pixel(cub->floor_ceiling, y, x, cub->map.ceiling_color);
			else
				mlx_put_pixel(cub->floor_ceiling, y, x, cub->map.floor_color);
			y++;
		}
		y = 0;
		x++;
	}
	if (mlx_image_to_window(cub->mlx, cub->floor_ceiling, 0, 0) < 0)
	{
		ft_printf("Error. Image problem\n");
		bye_bye(cub);
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

void	dda(t_game *cub)
{
	int		pixel_x;
	double	camera_x;

	pixel_x = 0;
	// if (cub->image)
	// 	mlx_delete_image(cub->mlx, cub->image);
	// cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	// if (!cub->image)
	// {
	// 	ft_printf("Error. Window problem\n");
	// 	bye_bye(cub);
	// }
	mlx_delete_image(cub->mlx, cub->image);
	cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
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
	// mlx_image_to_window(cub->mlx, cub->image, 0, 0);
	// if (mlx_image_to_window(cub->mlx, cub->image, 0, 0) < 0)
	// {
	// 	ft_printf("Error. Image problem\n");
	// 	bye_bye(cub);
	// }
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


void	perform_dda(t_game *cub)
{
	// while (cub->ray.map.x >= 0 && cub->ray.map.y >= 0 && cub->ray.map.x < WIDTH && cub->ray.map.y < HEIGHT && cub->map.cub_map[(int)cub->ray.map.y][(int)cub->ray.map.x] != '1')
	while (cub->map.cub_map[(int)cub->ray.map.y][(int)cub->ray.map.x] != '1')
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
	// cub->move_speed = 0.06;
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



void	free_ptrptr(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

void	close_cub(void *param)
{
	t_game	*cub;

	cub = (t_game *)param;
	bye_bye(cub);
	mlx_close_window(cub->mlx);
}

void	bye_bye(t_game *cub)
{
	if (cub->no)
		mlx_delete_texture(cub->no);
	if (cub->so)
		mlx_delete_texture(cub->so);
	if (cub->we)
		mlx_delete_texture(cub->we);
	if (cub->ea)
		mlx_delete_texture(cub->ea);
	if (cub->map.north_path)
		free(cub->map.north_path);
	if (cub->map.south_path)
		free(cub->map.south_path);
	if (cub->map.east_path)
		free(cub->map.east_path);
	if (cub->map.west_path)
		free(cub->map.west_path);
	if (cub->map.cub_map)
		free_ptrptr(cub->map.cub_map);
}
