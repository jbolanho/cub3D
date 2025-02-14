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

// # include 

typedef struct s_map
{
	size_t		wid;
	size_t		hei;
	char		*cub_map;
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

// 



//init
void    init(t_game *cub, int argc, char **argv);


//validate


//game
void	game(t_game *cub);
void	init_game(t_game *cub);
void	init_images(t_game *cub);
void	init_window(t_game *cub);
void	key_press(t_game *cub);

//bye_bye





#endif