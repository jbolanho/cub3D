#include "../include/cub.h"

void	init(t_game *cub)
{
	init_window(cub);
	init_images(cub);
	initial_pov(cub);
}

void	init_window(t_game *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!cub->mlx)
	{
		ft_printf("Error. MLX init error.\n");
		bye_bye(cub, EXIT_SUCCESS);
	}
	cub->time = mlx_get_time();
	cub->rotation_speed = 0.02;
	cub->move_speed = 0.06;
}

void	init_images(t_game *cub)
{
	cub->texture[NO] = mlx_load_png(cub->map.north_path);
	cub->texture[SO] = mlx_load_png(cub->map.south_path);
	cub->texture[EA] = mlx_load_png(cub->map.east_path);
	cub->texture[WE] = mlx_load_png(cub->map.west_path);
}

void	initial_pov(t_game *cub)
{
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
	init_background(cub);
	dda(cub);
	// draw_minimap(cub);
}

t_vector	vector(float x, float y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

void	init_background(t_game *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	cub->floor_ceiling = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->floor_ceiling)
	{
		ft_printf("Error. Window problem\n");
		bye_bye(cub, EXIT_SUCCESS);
	}
	while (x < HEIGHT)
	{
		while (y < WIDTH)
		{
			if (x < (int)(HEIGHT / 2))
				mlx_put_pixel(cub->floor_ceiling, y, x, cub->map.ceiling_color);
			else
				mlx_put_pixel(cub->floor_ceiling, y, x, cub->map.floor_color);
			y++;
		}
		y = 0;
		x++;
	}
	// if (mlx_image_to_window(cub->mlx, cub->floor_ceiling, 0, 0) < 0)
	// {
	// 	ft_printf("Error. Image problem\n");
	// 	bye_bye(cub, EXIT_SUCCESS);
	// }
	mlx_image_to_window(cub->mlx, cub->floor_ceiling, 0, 0);
}

void	dda(t_game *cub)
{
	int		i;
	
	i = 0;
	if (cub->image)
		mlx_delete_image(cub->mlx, cub->image);
	cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image)
	{
		ft_printf("Error. Image problem\n");
		bye_bye(cub, EXIT_SUCCESS);
	}
	while (i < WIDTH)
	{
		cub->ray.hit_wall = false;
		cub->ray.camera_x = 2 * i / (double)WIDTH - 1;
		cub->ray.map = vector(cub->position.x, cub->position.y);
		cub->ray.dir.x = cub->direction.x + cub->camera_plane.x * cub->ray.camera_x;
		cub->ray.dir.y = cub->direction.y + cub->camera_plane.y * cub->ray.camera_x;
		delta_dist(cub);
		step_and_side_distance(cub);
		perform_dda(cub);
		pixel_wall(cub, i);
		i++;
	}
	mlx_image_to_window(cub->mlx, cub->image, 0, 0);
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
	while (!cub->ray.hit_wall)
	{
		if (cub->ray.side_dist.x < cub->ray.side_dist.y)
		{
			cub->ray.side_dist.x += cub->ray.delta_dist.x;
			cub->ray.map.x += cub->ray.step.x;
			get_wall(cub, 0);
		}
		else
		{
			cub->ray.side_dist.y += cub->ray.delta_dist.y;
			cub->ray.map.y += cub->ray.step.y;
			get_wall(cub, 1);
		}
		if (cub->map.cub_map[(int)cub->ray.map.y][(int)cub->ray.map.x] == '1')
			cub->ray.hit_wall = true;
	}
	if (cub->ray.side == EA || cub->ray.side == WE)
		cub->ray.perp_dist = cub->ray.side_dist.x - cub->ray.delta_dist.x;
	else
		cub->ray.perp_dist = cub->ray.side_dist.y - cub->ray.delta_dist.y;
}

void	get_wall(t_game *cub, int x)
{
	if (x == 0 && cub->ray.dir.x > 0)
		cub->ray.side = EA;
	if (x == 0 && cub->ray.dir.x <= 0)
		cub->ray.side = WE;
	if (x == 1 && cub->ray.dir.y > 0)
		cub->ray.side = SO;
	if (x == 1 && cub->ray.dir.y <= 0)
		cub->ray.side = NO;
}

void	pixel_wall(t_game *cub, int i)
{
	t_vector	end;
	t_vector	start;

	cub->ray.line_hight = (int)(HEIGHT / cub->ray.perp_dist) + 1;
	start.x = (int)(- cub->ray.line_hight / 2 + HEIGHT / 2);
	start.y = i;
	if (start.x < 0)
		start.x = 0;
	end.x = (int)(cub->ray.line_hight / 2 + HEIGHT / 2);
	end.y = i;
	if (end.x >= HEIGHT)
		end.x = HEIGHT - 1;
	put_pixel(cub, start, end, cub->ray.side);
}

void	put_pixel(t_game *cub, t_vector start, t_vector end, int side)
{
	int			i;
	t_texture	tex;
	
	find_wall(cub, side, &tex);
	tex.position = (start.x - HEIGHT / 2 + cub->ray.line_hight / 2) * tex.step;
	i = start.x;
	while (i <= end.x)
	{
		tex.tex_y = (int)tex.position;
		if (tex.tex_y >= tex.image->height)
			tex.tex_y = tex.image->height - 1;
		tex.position += tex.step;
		tex.color = get_color(tex);
		tex.buffer[i] = tex.color;
		// if (tex.color != 0)
		// 	mlx_put_pixel(cub->image, start.y, i, tex.color);
		i++;
	}
	line(cub, start, end, tex.buffer);
}

void	find_wall(t_game *cub, int side, t_texture *tex)
{
	if (side == NO || side == SO)
		tex->wall_x = cub->position.x + cub->ray.perp_dist * cub->ray.dir.x;
	else
		tex->wall_x = cub->position.y + cub->ray.perp_dist * cub->ray.dir.y;
	tex->image = cub->texture[side];
	tex->wall_x -= floor(tex->wall_x);
	tex->tex_x = (int)tex->wall_x * (double)tex->image->width;
	tex->step = (double)tex->image->height / cub->ray.line_hight;
	ft_bzero(tex->buffer, HEIGHT);
}
int	get_color(t_texture tex)
{
	int32_t	pixel;
	
	pixel = *((int32_t *)tex.image->pixels) + (size_t)(tex.tex_y * tex.image->width + tex.tex_x);
	pixel = ((pixel & 0xFF) << 24) | ((pixel & 0xFF00) << 8) | ((pixel & 0xFF0000) >> 8) | ((pixel & 0xFF000000) >> 24);
	// printf("AQUIII %d\n", pixel);
	return (pixel);
}

// void	put_pixel(t_game *cub, int pixel)
// {
// 	int			y;
// 	int			wall_y;
// 	uint32_t	color;

// 	y = cub->tex.start_y;
// 	while (y < cub->tex.end_y)
// 	{
// 		cub->tex.texture_pos += cub->tex.texture_step;
// 		wall_y = (int)cub->tex.texture_pos;
// 		// wall_y = (int)cub->tex.texture_pos;
// 		if (wall_y < 0)
// 			wall_y = 0;
// 		if (wall_y >= (int)cub->walls->height)
// 			wall_y = cub->walls->height - 1;
// 		color = get_color(cub->walls, wall_y, cub->tex.texture_x);
// 		mlx_put_pixel(cub->image, pixel, y, color);
// 		y++;
// 	}
// }

// int	get_color(t_texture tex)
// {
// 	int		pos;
// 	uint8_t	*pixel;
// 	uint32_t color;

// 	// if (x < 0 || x >= (int)walls->width || y < 0 || y >= (int)walls->height)
// 	// 	return (0);
// 	pos = tex.tex_y * tex.image->width + tex.tex_x;
// 	pos *= tex.image->bytes_per_pixel;
// 	pixel = &tex.image->pixels[pos];
// 	color = pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3];
// 	return (color);
// }

void	line(t_game *cub, t_vector start, t_vector end, int buffer[HEIGHT])
{
	t_draw	line;

	draw_setup(&line, start, end);
	// printf("AQUIII \n");
	while(true)
	{
		if (buffer[line.i] != 0)
			mlx_put_pixel(cub->image, start.y, start.x, buffer[line.i]);
		line.i++;
		if (start.x == end.x && start.y == end.y)
			break ;
		if (line.error * 2 >= -line.delta_y)
		{
			if (start.x == end.x)
				break ;
			line.error -= line.delta_y;
			start.x += line.step_x;
		}
		if (line.error * 2 <= line.delta_x)
		{
			if (start.y == end.y)
				break ;
			line.error += line.delta_x;
			start.x += line.step_y;
		}valgrind ./cub3D ./maps/map1.cub
		// printf("AQUIII2 %d\n", line.i);
	}
}

void	draw_setup(t_draw *line, t_vector start, t_vector end)
{
	line->i = (int)start.x;
	line->step_x = 1;
	line->step_y = 1;
	line->delta_y = fabs(end.y - start.y);
	line->delta_x = fabs(end.x - start.x);
	if (start.x > end.x)
		line->step_x = -1;
	if (start.y > end.y)
		line->step_y = -1;	
	line->error = line->delta_x - line->delta_y;
	// printf("AQUIII 1\n");
}


void game(t_game *cub)
{
	mlx_loop_hook(cub->mlx, player_pov, cub);
	mlx_loop(cub->mlx);
}

void	player_pov(void *param)
{
	t_game	*cub;
	
	cub = (t_game *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		bye_bye(cub, EXIT_SUCCESS);
		// mlx_close_window(cub->mlx);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		go_ahead(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		moon_walk(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		crab_walk(cub, MLX_KEY_A);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		crab_walk(cub, MLX_KEY_D);	
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		look_movements(cub, MLX_KEY_LEFT)	;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		look_movements(cub, MLX_KEY_RIGHT);
	frame_speed(cub);
	dda(cub);
	// draw_minimap(cub);
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

void	look_movements(t_game *cub, int key)
{
	if (key == MLX_KEY_LEFT)
	{
		cub->direction = rotate_vector(cub->direction, -1.5);
		cub->camera_plane = rotate_vector(cub->camera_plane, -1.5);
	}
	if (key == MLX_KEY_RIGHT)
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

void	frame_speed(t_game *cub)
{
	static mlx_image_t	*image;
	static int			fps;
	char				*fps_text;
	char				*fps_nbr;
	int					curr;
	
	fps += 1;
	curr = (int)mlx_get_time();
	if (cub->frame_time < curr)
	{
		fps_nbr = ft_itoa((int)fps);
		fps_text = ft_strjoin("FPS:", fps_nbr);
		free(fps_nbr);
		fps = 0;
		cub->frame_time = mlx_get_time();
		if (image)
		mlx_delete_image(cub->mlx, image);
		image = mlx_put_string(cub->mlx, fps_text, WIDTH - 80, HEIGHT - 790);
		free(fps_text);
	}
}

void	bye_bye(t_game *cub, int code)
{
	
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
	if (cub->mlx)
	{
		free_images(cub);
		mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
	}
	exit(code);
}

void	free_images(t_game *cub)
{
	if (cub->texture[NO])
		mlx_delete_texture(cub->texture[NO]);
	if (cub->texture[SO])
		mlx_delete_texture(cub->texture[SO]);
	if (cub->texture[WE])
		mlx_delete_texture(cub->texture[WE]);
	if (cub->texture[EA])
		mlx_delete_texture(cub->texture[EA]);
	if (cub->image)
		mlx_delete_image(cub->mlx, cub->image);
	if (cub->floor_ceiling)
		mlx_delete_image(cub->mlx, cub->floor_ceiling);
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
	
	


// void	draw_minimap(t_game *cub)
// {
// 	int			x;
// 	int			y;
// 	const int	rx = ceil(WIDTH / RATIO);
// 	const int	ry = ceil(HEIGHT / RATIO);

// 	y = -1;
// 	if (cub->minimap)
// 		mlx_delete_image(cub->mlx, cub->minimap);
// 	cub->minimap = mlx_new_image(cub->mlx, cub->map.x * ry, cub->map.y * rx);
// 	if (!cub->minimap)
// 		cuberror("Oops, we had a problem with the minimap. ˙◠˙", cub);
// 	while (++y < cub->map.y * rx)
// 	{
// 		x = 0;
// 		while (x < (int)(ft_strlen(cub->map_matrix[(int)(y / rx)]) * ry))
// 		{
// 			if (cub->map_matrix[(int)(y / rx)][(int)(x / ry)] == '1'
// 				|| cub->map_matrix[(int)(y / rx)][(int)(x / ry)] == '2')
// 				mlx_put_pixel(cub->minimap, x, y, 0x00000095);
// 			else if (cub->map_matrix[(int)(y / rx)][(int)(x / ry)] != ' ')
// 				mlx_put_pixel(cub->minimap, x, y, 0xffffff95);
// 			x++;
// 		}
// 	}
// 	draw_player_on_minimap(cub);
// }

// void	draw_player_on_minimap(t_game *cub)
// {
// 	int			x;
// 	int			y;
// 	const int	rx = ceil(WIDTH / RATIO);
// 	const int	ry = ceil(HEIGHT / RATIO);

// 	if (cub->miniplayer)
// 		mlx_delete_image(cub->mlx, cub->miniplayer);
// 	cub->miniplayer = mlx_new_image(cub->mlx, rx, ry);
// 	if (!cub->miniplayer)
// 		cuberror("Oops, found an issue on the minimap. ˙◠˙", cub);
// 	x = -1;
// 	while (++x < rx)
// 	{
// 		y = -1;
// 		while (++y < ry)
// 			mlx_put_pixel(cub->miniplayer, x, y, 0xc1121f95);
// 	}
// 	mlx_image_to_window(cub->mlx, cub->minimap, MAP_OFFSET, MAP_OFFSET);
// 	mlx_image_to_window(cub->mlx, cub->miniplayer,
// 		cub->p1.x * ry + MAP_OFFSET - (int)(ry / 3),
// 		cub->p1.y * rx + MAP_OFFSET - (int)(rx / 3));
// 	cub->screen->instances->z = 1;
// 	cub->minimap->instances->z = 2;
// 	cub->miniplayer->instances->z = 3;
// }




// mlx_put_pixel(cub->image, pixel, y, color);
// if (wall_y < 0)
// 	wall_y = 0;
// if (cub->tex.texture_pos < 0)
// 		cub->tex.texture_pos = 0;

// if(cub->ray.side == 0 && cub->ray.dir.x > 0)
// 	cub->tex.tex_x = cub->walls->width - cub->tex.tex_x - 1;
// if(cub->ray.side == 1 && cub->ray.dir.x < 0)
// 	cub->tex.tex_x = cub->walls->width - cub->tex.tex_x - 1;