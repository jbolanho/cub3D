/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:52:56 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/25 15:17:15 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/cub.h"

// // void    init(t_game *cub)
// // {
// //     cub->map.north_path = NULL;
// // 	cub->map.south_path = NULL;
// // 	cub->map.east_path = NULL;
// // 	cub->map.west_path = NULL;
// // 	cub->map.floor_color = 0;
// // 	cub->map.ceiling_color = 0;
// // }

// //ajustar com as cores do mapa

// void	define_initial_pov(t_game *cub)
// if (cub->direction.x < 0)
// {
// 	cub->ray.step_x = -1;
// 	cub->ray.side_dist_x = (cub->map.p1_x - cub->ray.map_x)	* cub->ray.delta_dist_x;
// }
// else
// {
// 	cub->ray.step_x = 1;
// 	cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->map.p1_x) * cub->ray.delta_dist_x;
// }
// if (cub->direction.y < 0)
// {
// 	cub->ray.step_y = -1;
// 	cub->ray.side_dist_y = (cub->map.p1_y - cub->ray.map_y)	* cub->ray.delta_dist_y;
// }
// else
// {
// 	cub->ray.step_y = 1;
// 	cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->map.p1_y) * cub->ray.delta_dist_y;
// }


// void	moon_walk(t_game *cub)
// {
// 	int	x1;
// 	int	y1;
// 	int	x2;
// 	int	y2;
	
// 	x1 = (int)(cub->position.x - cub->direction.x * cub->move_speed);
// 	y1 = (int)cub->position.y;
// 	x2 = (int)cub->position.x;
// 	y2 = (int)(cub->position.y - cub->direction.y * cub->move_speed);

// 	if (cub->map_matrix[y1][x1] != '1')
// 		cub->position.x -= cub->direction.x * cub->move_speed;
// 	if (cub->map_matrix[y2][x2] != '1')
// 		cub->position.y -= cub->direction.y * cub->move_speed;
// }

// void	go_ahead(t_game *cub)
// {
// 	int	x1;
// 	int	y1;
// 	int	x2;
// 	int	y2;

// 	x1 = (int)(cub->position.x + cub->direction.x * cub->move_speed);
// 	y1 = (int)cub->position.y;
// 	x2 = (int)cub->position.x;
// 	y2 = (int)(cub->position.y + cub->direction.y * cub->move_speed);

// 	if (cub->map_matrix[y1][x1] != '1')
// 		cub->position.x += cub->direction.x * cub->move_speed;
// 	if (cub->map_matrix[y2][x2] != '1')
// 		cub->position.y += cub->direction.y * cub->move_speed;
// }

// void	crab_walk(t_game *cub, int key)
// {
// 	int	x1;
// 	int	y1;
// 	int	x2;
// 	int	y2;

// 	x1 = (int)(cub->position.x + cub->direction.y * cub->move_speed);
// 	y1 = (int)(cub->position.y - cub->direction.x * cub->move_speed);
// 	x2 = (int)(cub->position.x - cub->direction.y * cub->move_speed);
// 	y2 = (int)(cub->position.y + cub->direction.x * cub->move_speed);

// 	if (key == MLX_KEY_A && (cub->map_matrix[y1][x1] != '1' ))
// 	{
// 		cub->position.x += cub->direction.y * cub->move_speed;
// 		cub->position.y -= cub->direction.x * cub->move_speed;
// 	}	
// 	if (key == MLX_KEY_D && (cub->map_matrix[y2][x2] != '1'))
// 	{
// 		cub->position.x -= cub->direction.y * cub->move_speed;
// 		cub->position.y += cub->direction.x * cub->move_speed;
// 	}
// }
// void	look_right(t_game *cub)
// {
// 	double	old_dir;
// 	double	old_plane_x;

// 	old_dir = cub->direction.x;
// 	old_plane_x = cub->camera_plane.x;
// 	cub->direction.x = cub->direction.x * cos(cub->rotation_speed)
// 		- cub->direction.y * sin(cub->rotation_speed);
// 	cub->direction.y = old_dir * sin(cub->rotation_speed)
// 		+ cub->direction.y * cos(cub->rotation_speed);
// 	cub->camera_plane.x = cub->camera_plane.x * cos(cub->rotation_speed)
// 		- cub->camera_plane.y * sin(cub->rotation_speed);
// 	cub->camera_plane.y = old_plane_x * sin(cub->rotation_speed)
// 		+ cub->camera_plane.y * cos(cub->rotation_speed);
// }

// void	look_left(t_game *cub)
// {
// 	double	old_dir;
// 	double	old_plane_x;

// 	old_dir = cub->direction.x;
// 	old_plane_x = cub->camera_plane.x;
// 	cub->direction.x = cub->direction.x * cos(-cub->rotation_speed)
// 		- cub->direction.y * sin(-cub->rotation_speed);
// 	cub->direction.y = old_dir * sin(-cub->rotation_speed)
// 		+ cub->direction.y * cos(-cub->rotation_speed);
// 	cub->camera_plane.x = cub->camera_plane.x * cos(-cub->rotation_speed)
// 		- cub->camera_plane.y * sin(-cub->rotation_speed);
// 	cub->camera_plane.y = old_plane_x * sin(-cub->rotation_speed)
// 		+ cub->camera_plane.y * cos(-cub->rotation_speed);
// }




// void	close_cub(void *param)
// {
// 	t_game	*cub;

// 	cub = (t_game *)param;
// 	free_texture(cub);
// 	mlx_close_window(cub->mlx);
// }

// void	free_texture(t_game *cub)
// {
// 	int i;

// 	i = 0;
// 	while(i < 4)
// 	{
// 		if(cub->texture[i])
// 			mlx_delete_texture(cub->texture[i]);
// 		i++;
// 	}	
// 	// if(cub)
// 	// 	free_map(cub->map);	
// }

// void	free_map(t_map	*map)
// {
// 	if(map->north_path)
// 		free(map->north_path);
// 	if(map->south_path)
// 		free(map->south_path);
// 	if(map->east_path)
// 		free(map->east_path);
// 	if(map->west_path)
// 		free(map->west_path);
// 	if(map->cub_map)
// 		free_matrix(map->cub_map);
// 	if(map)
// 		free(map);
// }

// void close_cub(void *param)
// {
// 	t_game *cub;
// 	cub = (t_game *)param;
// 	delete_memory(cub);
// 	mlx_close_window(cub->mlx);
// }

// void delete_memory(t_game *cub)
// {
// 	if (cub->no)
// 	mlx_delete_texture(cub->no);
// 	if (cub->so)
// 	mlx_delete_texture(cub->so);
// 	if (cub->we)
// 	mlx_delete_texture(cub->we);
// 	if (cub->ea)
// 	mlx_delete_texture(cub->ea);
// 	if (cub)
// 	//free_data(cub->map);
// }



// void	raycast(t_game *cub)
// {
//     // int	i;

//     // i = 0;
//     printf("AQUI  1 \n");
// 	if (cub->walls)
//         mlx_delete_image(cub->mlx, cub->walls);
//     cub->walls = mlx_new_image(cub->mlx, cub->window_wid, cub->window_hei);
//     if (!cub->walls)
//     {
//         printf("Error. Walls don't work");
//         //bye_bye(cub, );
//     }
// 	printf("AQUI  2 \n");
	
//     // while (i < (int)cub->window_wid)
//     // {
//     //     init_ray_struct(cub, i);
// 	// 	delta_dist(cub);
// 	// 	wall_distance(cub);
// 	// 	draw_line(cub, i);
// 	// 	i++;
//     // }
// 	printf("AQUI  3 \n");
// 	mlx_image_to_window(cub->mlx, cub->walls, 0, 0);
// }

// void	init_ray_struct(t_game *cub, int i)
// {
// 	cub->ray.collide = false;
// 	cub->ray.camera_x = 2 * i / (double)cub->window_wid - 1;
// 	cub->ray.map_x = cub->map.p1_x;
// 	cub->ray.map_y = cub->map.p1_y;
// 	cub->ray.dir_x = cub->direction.x + cub->camera_plane.x * cub->ray.camera_x;
// 	cub->ray.dir_y = cub->direction.y + cub->camera_plane.y * cub->ray.camera_x;
// }



// void	wall_distance(t_game *cub)
// {
// 	while (!cub->ray.collide)
// 	{
// 		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
// 		{
// 			cub->ray.side_dist_x += cub->ray.delta_dist_x;
// 			cub->ray.map_x += cub->ray.step_x;
// 			wall_side(cub, X);
// 		}
// 		else
// 		{
// 			cub->ray.side_dist_y += cub->ray.delta_dist_y;
// 			cub->ray.map_y += cub->ray.step_y;
// 			wall_side(cub, Y);
// 		}
// 		if (cub->map_matrix[(int)cub->ray.map_y][(int)cub->ray.map_x] == '1')
// 			cub->ray.collide = true;
// 	}
// 	if (cub->ray.side == EA || cub->ray.side == WE)
// 		cub->ray.perp_wall_dist = cub->ray.side_dist_x - cub->ray.delta_dist_x;
// 	else
// 		cub->ray.perp_wall_dist = cub->ray.side_dist_y - cub->ray.delta_dist_y;
// }

// void	wall_side(t_game *cub, int axis)
// {
// 	if (axis == X && cub->ray.dir_x > 0)
// 		cub->ray.side = EA;
// 	if (axis == X && cub->ray.dir_x <= 0)
// 		cub->ray.side = WE;
// 	if (axis == Y && cub->ray.dir_y > 0)
// 		cub->ray.side = SO;
// 	if (axis == Y && cub->ray.dir_y <= 0)
// 		cub->ray.side = NO;
// }

// void	draw_line(t_game *cub, int i)
// {
// 	t_vector	end;
// 	t_vector	start;
	
// 	cub->ray.line_hei = (int)(cub->window_hei / cub->ray.perp_wall_dist) + 1;
// 	start.y = i;
// 	start.x = (int)(-cub->ray.line_hei / 2 + cub->window_hei / 2);
// 	if (start.x < 0)
// 		start.x = 0;
// 	end.y = i;
// 	end.x = (int)(cub->ray.line_hei / 2 + cub->window_hei / 2);
// 	if (end.x >= (int)cub->window_hei)
// 		end.x = cub->window_hei - 1;
// 	texture(cub, start, end, cub->ray.side);
// }

// void	texture(t_game *cub, t_vector start, t_vector end, int side)
// {
// 	int		i;
// 	t_tex	tex;

// 	side_texture(cub, side, &tex);
// 	tex.position = (start.x - cub->window_hei / 2 + cub->ray.line_hei / 2) * tex.step;
// 	i = start.x;
// 	while( i <= end.x)
// 	{
// 		tex.y = (int)tex.position & (tex.img->height - 1);
// 		tex.position += tex.step;
// 		tex.color = pixel_color(tex);
// 		tex.buffer[i] = tex.color;
// 		i++;
// 	}
// 	put_pixel(cub, start, end, tex.buffer);
// }

// void	side_texture(t_game *cub, int side, t_tex *tex)
// {
// 	if (side == NO || side == SO)
// 		tex->area = cub->position.x + cub->ray.perp_wall_dist * cub->ray.dir_x;
// 	if (side == EA || side == WE)
// 		tex->area = cub->position.y + cub->ray.perp_wall_dist * cub->ray.dir_y;
// 	tex->img = cub->texture[side];
// 	tex->area -= floor(tex->area);
// 	tex->x = (int)(tex->area * (double)tex->img->width);
// 	tex->step = (double)tex->img->height / cub->ray.line_hei;
// 	ft_bzero(tex->buffer, cub->window_hei);
// }

// int	pixel_color(t_tex tex)
// {
// 	int32_t	pixel;

// 	pixel = *((int32_t *)tex.img->pixels
// 			+ (size_t)(tex.y * tex.img->width + tex.x));
// 	pixel = ((pixel & 0xFF) << 24) | ((pixel & 0xFF00) << 8)
// 		| ((pixel & 0xFF0000) >> 8) | ((pixel & 0xFF000000) >> 24);
// 	return (pixel);
// }

// void	put_pixel(t_game *cub, t_vector start, t_vector end, int buffer[600])
// {
// 	int i;
// 	int error;
// 	int	step_x;
// 	int step_y;
// 	int delta_x;
// 	int delta_y;

// 	i = start.x;
// 	step_x = 1;
// 	step_y = 1;
// 	delta_x = fabs(end.x - start.x);
// 	delta_y = fabs(end.y - start.y);
// 	if (start.x > end.x)
// 		step_x = -1;
// 	if (start.y > end.y)
// 		step_y = -1;
// 	error = delta_x - delta_y;
// 	while (true)
// 	{
// 		if (buffer[i] != 0)
// 			mlx_put_pixel(cub->walls, start.y, start.x, buffer[i]);
// 		i++;
// 		if (start.x == end.x && start.y == end.y)
// 			break;
// 		if (error * 2 >= -delta_y)
// 		{
// 			if(start.x == end.x)
// 				break;
// 			error -= delta_y;
// 			start.x += step_x;
// 		}
// 		if (error * 2 <= delta_x)
// 		{
// 			if (start.y == end.y)
// 				break;
// 			error += delta_x;
// 			start.y += step_y;
// 		}
// 	}	
// }