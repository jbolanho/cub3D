
#include "../include/cub.h"

void	game(t_game *cub)
{
	// printf("AQUI  6 \n");
	
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
	frame_speed(cub);
	// init_background(cub);
	raycast(cub);
	// printf("AQUI  10 \n");
}

void take_input(t_game *cub)
{
	float   x;
    float   y;
    float   camera_mov;
    float   move_speed;
	
    x = cub->map.p1_x;
    y = cub->map.p1_y;
    camera_mov = 1;
    move_speed = cub->frame_time * 4;
	// printf("AQUI  7 \n");
    if  (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		x += cub->direction.x * move_speed;
		y += cub->direction.y * move_speed;
	}
    if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		x -= cub->direction.x * move_speed;
		y -= cub->direction.y * move_speed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		x += cub->camera_plane.x * move_speed;
		y += cub->camera_plane.x * move_speed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		x -= cub->camera_plane.x * move_speed;
		y -= cub->camera_plane.x * move_speed;
	}
	if(can_go(cub, x, y))
	{
		cub->position.x = cub->position.x + camera_mov * (x - cub->position.x);
		cub->position.y = cub->position.y + camera_mov * (y - cub->position.y);
	}
    look_movements(cub);
}

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
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->direction = rotate_vector(cub->direction, -1.5);
		cub->camera_plane = rotate_vector(cub->camera_plane, -1.5);
	}	
	
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
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


void	close_cub(void *param)
{
	t_game	*cub;

	cub = (t_game *)param;
	free_texture(cub);
	mlx_close_window(cub->mlx);
}

void	free_texture(t_game *cub)
{
	if (cub->no)
		mlx_delete_texture(cub->no);
	if (cub->so)
		mlx_delete_texture(cub->so);
	if (cub->we)
		mlx_delete_texture(cub->we);
	if (cub->ea)
		mlx_delete_texture(cub->ea);
	if(cub)
		free_map(&cub->map);	
}

void	free_map(t_map	*map)
{
	if(map->north_path)
		free(map->north_path);
	if(map->south_path)
		free(map->south_path);
	if(map->east_path)
		free(map->east_path);
	if(map->west_path)
		free(map->west_path);
	if(map->cub_map)
		free_ptrptr(map->cub_map);
	if(map)
		free(map);
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