/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:13:02 by jbolanho          #+#    #+#             */
/*   Updated: 2025/03/18 14:56:43 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	init_struct(t_game *cub)
{
	cub->map.north_path = NULL;
	cub->map.east_path = NULL;
	cub->map.south_path = NULL;
	cub->map.west_path = NULL;
	cub->map.floor_color = 0;
}

int	main(int argc, char **argv)
{
	t_game	cub;

	init_struct(&cub);
	validate(argc, argv, &cub);
	// printf("AQUIIIII 1");
	init(&cub);
	game(&cub);
	bye_bye(&cub, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

