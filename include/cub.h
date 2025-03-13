/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:10:14 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/25 17:23:30 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

// # include 

# define WIDTH		1000
# define HEIGHT		800
# define LEFT_ROTATE -0.5
# define RIGHT_ROTATE 0.5
// # define
// # define



typedef struct s_map
{
	int			wid;
	int			hei;
	char		**cub_map;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	int			p1_x;
	int			p1_y;
	int			p1_pov;
}		t_map;

enum e_side
{
	N,
	S,
	E,
	W
};

// NO,
// SO,
// EA,
// WE,
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	// bool	collide;
	// float	side_dist_x;
	// float	side_dist_y;
	// float	delta_dist_x;
	// float	delta_dist_y;
	// float	dir_x;
	// float	dir_y;
	// int		map_x;
	// int		map_y;
	// int		step_x;
	// int		step_y;
	// enum e_side	side;
	// int		perp_wall_dist;
	// int		camera_x;
	// int		camera_y;
	// int		line_hei;
	t_vector	direction;
	t_vector	camera_pixel;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	map;
	t_vector	step;
	int			collide;
	float		perp_dist;
	float		plane_multi;
	float		wall_collide;

}		t_ray;

typedef struct s_texture
{
	int		height;
	int		start_y;
	int		end_y;
	int		texture_x;
	int		texture_y;
	float	point_x;
	float	texture_step;
	float	texture_pos;
	
	// double	position;
	// double	step;
	// double	area;
	// double	x;
	// double	y;
	// int		color;
	// int		buffer[600];
	// mlx_texture_t	*img;	
}		t_tex;

typedef struct s_key
{
	bool	left;
	bool	right;
	bool	w;
	bool	s;
	bool	a;
	bool	d;
}	t_key;

typedef struct s_game
{
	mlx_t			*mlx;
	t_map			map;
	t_ray			ray;
	t_tex			tex;
	t_key			key;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	mlx_texture_t	*walls;
	mlx_image_t		*floor_ceiling;
	mlx_image_t		*image;
	int				*texture[4];
	t_vector		position;
	t_vector		direction;
	t_vector		camera_plane;
	int				collide;
	float			frame_time;
	double			move_speed;
	double			rotation_speed;
	// int		frame;

}		t_game;

// apagar
void	copy_map(t_game *cub);

//init
void    init(t_game *cub);
void	init_images(t_game *cub);
void	init_window(t_game *cub);
void	init_background(t_game *cub);
void	initial_pov(t_game *cub);
t_vector create(float x, float y);
void    key_data(mlx_key_data_t pressed, void *param);

//game
void		game(t_game *cub);
// int		init_game(t_game *cub);
void	player_pov(void *param);
void	moon_walk(t_game *cub);
void	go_ahead(t_game *cub);
void	crab_walk(t_game *cub, int key);
// void	look_right(t_game *cub);
// void	look_left(t_game *cub);


// void	take_input(t_game *cub);
// void	free_texture(t_game *cub);
// void	update_image(t_game *cub);
void take_input(t_game *cub);
bool	can_go(t_game *cub, float x, float y);
int	minus_or_not(float value);
void    look_movements(t_game *cub);
t_vector	rotate_vector(t_vector v, float angle);
void    frame_speed(t_game *cub);

//algorithm
void	raycast(t_game *cub);
// void	init_ray_struct(t_game *cub, int i);
void	delta_dist(t_game *cub);
void    wall_dist(t_game *cub);
void	not_collide(t_game *cub);
void	pixel_wall(t_game *cub, int pixel);
mlx_texture_t	*get_wall(t_game *cub);
void	wall_and_background(t_game *cub);
void	find_pixel_wall(t_game *cub);
void	put_pixel(t_game *cub, int pixel);
uint32_t	get_color(mlx_texture_t	*walls, int y, int x);
// void	define_initial_pov(t_game *cub);
// void	wall_distance(t_game *cub);
// void	wall_side(t_game *cub, int axis);
// void	draw_line(t_game *cub, int i);
// void	texture(t_game *cub, t_vector start, t_vector end, int side);
// void	side_texture(t_game *cub, int side, t_tex *tex);
// int		pixel_color(t_tex tex);
// void	put_pixel(t_game *cub, t_vector start, t_vector end, int buffer[600]);
// mlx_texture_t *get_texture(t_game *cub, const char *side);

void	free_map(t_map	*map);
void	free_ptrptr(char **cmd);
void	free_texture(t_game *cub);
void	close_cub(void *param);
void	bye_bye(t_game *cub);

// check_path
void    check_path(t_map *map, char *temp, char *line_cpy);
void	copy_path(char **texture, char *temp, char *info, char *line_cpy);
void	cut_path(char *temp, char *line_cpy, char **texture);
void	after_path(char *temp, char *line_cpy);

//check_colors
void	check_colors(t_map *map, char *temp);
void	copy_rgb(char **texture, char *temp, char *info);
void	cut_rgb(uint32_t surface, char *temp);
void    make_rgb_array(char ***rgb, char *temp);

//validate_n_process
void	process_argv1(char *argv, t_map *map);
void	check_header(t_map *map, char *temp, int *fd);

//validate_utils
int open_file(char *argv);
int	is_space(char c);
uint32_t	convert_rgb(int r, int g, int b);

//validate
void	validate(int argc, char **argv, t_game *cub);
void	check_argc(int argc);
void	check_dotcub(char *argv);



#endif