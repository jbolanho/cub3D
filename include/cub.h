/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:10:14 by jbolanho          #+#    #+#             */
/*   Updated: 2025/04/14 18:15:51 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define WIDTH		1000
# define HEIGHT		800

typedef struct s_map
{
	char		**cub_map;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	int			player_pov;
	int			player_x;
	int			player_y;
	int			height;
	int			width;	
}		t_map;

enum e_side
{
	N,
	S,
	E,
	W
};

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	map;
	t_vector	step;
	bool		hit_wall;
	int			side;
	double		perp_dist;
}		t_ray;

typedef struct s_texture
{
	int				height;
	int				start_y;
	int				end_y;
	int				texture_x;
	float			texture_step;
	float			texture_pos;
	double			point_x;
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
	mlx_image_t		*image;
	t_vector		position;
	t_vector		direction;
	t_vector		camera_plane;
	double			frame_time;
	double			move_speed;
	double			rotation_speed;
}		t_game;

//main
void			init_struct(t_game *cub);

//validate
void			validate(int argc, char **argv, t_game *cub);
void			check_argc(int argc, t_map *map);
void			check_dotcub(char *argv, t_map *map);
void			process_argv1(char *argv, t_map *map);
int				open_file(char *argv, t_map *map);

// check_header
char			*check_header(t_map *map, char *temp, int *fd);
void			handle_header(int fd, t_map *map);
void			check_after_header(char *temp, t_map *map);
void			missing_info(t_map *map);

// check_path
void			check_path(t_map *map, char *temp, char *line_cpy);
void			copy_path(char **texture, char *temp,
					t_map *map, char *line_cpy);
void			cut_path(char *temp, char *line_cpy,
					char **texture, t_map *map);
void			after_path(char *temp, char *line_cpy, t_map *map);

//check_colors
void			check_colors(t_map *map, char *temp);
void			copy_rgb(uint32_t *color, char *line_cpy, t_map *map);
void			cut_rgb(uint32_t *surface, char *temp, t_map *map, char *orig);
char			**cut_rgb_tokens(char *temp, t_map *map, char *orig);
void			make_rgb_array(char ***rgb, char *temp, t_map *map, char *orig);

//check_map
void			check_map(t_map *map, char *argv);
void			get_map(t_map *map, char *argv);
int				map_size(int fd, t_map *map);
void			copy_map(t_map *map, char *argv);
void			process_map_line(t_map *map, char *temp,
					int *start, int *map_state);

//check_walls
void			check_walls(t_map *map);
void			check_wall_surroundings(t_map *map, int line, int column);
char			safe_map_get(t_map *map, int y, int x);
int				is_player_or_space(char c);
void			print_wall_error(int line, int column, t_map *map);

//check_player
void			check_player(t_map *map);
int				is_player(char c, t_map *map);
void			count_player(t_map *map, int line, int col, int *count);
void			check_extra_after_map(t_map *map, char *temp,
					char *orig, int map_state);
void			check_chr(t_map *map, const char *str);

//init
void			init(t_game *cub);
void			init_window(t_game *cub);
void			init_images(t_game *cub);
void			initial_pov(t_game *cub);
t_vector		vector(float x, float y);

//game
int				game(t_game *cub);
void			player_pov(void *param);
void			init_background(t_game *cub);
void			frame_speed(t_game *cub);

//key_data
void			key_data(mlx_key_data_t pressed, void *param);
void			take_input(t_game *cub);
void			moon_walk(t_game *cub);
void			go_ahead(t_game *cub);
void			key_release(t_game *cub, mlx_key_data_t pressed);

//key_data_utils
void			crab_walk(t_game *cub, int key);
void			look_movements(t_game *cub);
t_vector		rotate_vector(t_vector v, float angle);

//algorithm
void			dda(t_game *cub);
void			delta_dist(t_game *cub);
void			step_and_side_distance(t_game *cub);
void			perform_dda(t_game *cub);
void			pixel_wall(t_game *cub, int pixel);

//algorithm_utils
mlx_texture_t	*get_wall(t_game *cub);
void			wall_and_background(t_game *cub);
void			find_pixel_wall(t_game *cub);
void			put_pixel(t_game *cub, int pixel);
uint32_t		get_color(mlx_texture_t	*walls, int y, int x);

//bye_bye
void			free_ptrptr(char **cmd);
void			close_cub(void *param);
void			bye_bye(t_game *cub, int code);
void			bye_mlx(t_game *cub);
void			bye_game(t_map *map);

//utils
int				is_space(char c);
uint32_t		convert_rgb(int r, int g, int b);
void			allocate_matrix(t_map *map, int size);
void			print_map(t_map *map);
void			exit_rgb_error(t_map *map, char *temp,
					char *orig, const char *msg);

#endif