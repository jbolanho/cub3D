/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:10:14 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/13 16:42:40 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"

# include <stdio.h>
# include <math.h>
// # include 

# define X		0;
# define Y		1;


typedef struct s_map
{
	int			wid;
	int			hei;
	char		*cub_map;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	int			p1_x;
	int			p1_y;
	
}		t_map;

enum e_side
{
	NO,
	SO,
	EA,
	WE,
};

typedef struct s_ray
{
	bool	collide;
	int		side_dist_x;
	int		side_dist_y;
	int		delta_dist_x;
	int		delta_dist_y;
	int		dir_x;
	int		dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	enum e_side	side;
	int		perp_wall_dist;
	int		camera_x;

}		t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	t_map			map;
	t_ray			ray;
	int				time;
	size_t			window_wid;
	size_t			window_hei;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	mlx_image_t		*walls;
	mlx_image_t		*floor_ceiling;
	char			**map_matrix;
	int				direction_x;
	int				direction_y;
	int				camera_plane_x;
	int				camera_plane_y;
}		t_game;


//init
void    init(t_game *cub, int argc, char **argv);


//validate


//game
void	game(t_game *cub);
void	init_game(t_game *cub);
void	init_images(t_game *cub);
void	init_window(t_game *cub);
void	key_press(void *param);
void	init_background(t_game *cub);

//algorithm
void	algorithm(t_game *cub);
void	init_ray_struct(t_game *cub, int i);
void	delta_dist(t_game *cub);
void	calculate_side_distance(t_game *cub);
void	wall_distance(t_game *cub);
void	wall_side(t_game *cub, int axis);

//bye_bye





#endif