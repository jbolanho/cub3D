/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:13:02 by jbolanho          #+#    #+#             */
/*   Updated: 2025/03/31 16:33:36 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	fake_data(t_game *cub)
{
	// uint32_t	nb_floor;
	// uint32_t	nb_ceil;

	// nb_floor = get_rgba(169, 169, 169, 255);
	// nb_ceil = get_rgba(230, 230, 230, 255);
	cub->map.cub_map = NULL; 
	cub->map.north_path = NULL;
	cub->map.south_path = NULL;
	cub->map.east_path = NULL;
	cub->map.west_path = NULL;
	cub->map.floor_color = 0;
	cub->map.ceiling_color = 0;
	// cub->map.p1_x = 5;
	// cub->map.p1_y = 4;
	// cub->map.p1_pov = S;
	// copy_map(cub);
}
int	main(int argc, char **argv)
{
	t_game	cub;

	fake_data(&cub);
	validate(argc, argv, &cub);
	init(&cub);
	game(&cub);
	//bye_bye(&cub);
	return (EXIT_SUCCESS);
}
