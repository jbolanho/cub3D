/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:10:14 by jbolanho          #+#    #+#             */
/*   Updated: 2025/03/11 17:45:57 by anacaro5         ###   ########.fr       */
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
#include <fcntl.h>
#include <unistd.h>


// # include 

typedef struct s_map
{
	//int			wid;
	//int			hei;
	char		**cub_map;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
	uint32_t	floor_color;
	uint32_t	ceiling_color;

}		t_map;

typedef struct s_game
{
	mlx_t			*mlx;
	t_map			map;
	int				time;
	size_t			window_wid;
	size_t			window_hei;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	mlx_image_t		*floor_ceiling;
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


// check_path
void    check_path(t_map *map, char *temp, char *line_cpy);
void	copy_path(char **texture, char *temp, char *info, char *line_cpy);
void	cut_path(char *temp, char *line_cpy, char **texture);
void	after_path(char *temp, char *line_cpy);

//check_colors
void	check_colors(t_map *map, char *temp, char *line_cpy);
void	copy_rgb(uint32_t *color, char *line_cpy);
void	cut_rgb(uint32_t *surface, char *temp);
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


void	check_size(t_map *map, char *temp, char *argv);

void	check_map(t_map *map, char *argv);

#endif