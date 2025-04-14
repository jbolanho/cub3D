/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:13:02 by jbolanho          #+#    #+#             */
/*   Updated: 2025/04/14 17:17:52 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	init_struct(t_game *cub)
{
	cub->map.north_path = NULL;
	cub->map.east_path = NULL;
	cub->map.south_path = NULL;
	cub->map.west_path = NULL;
	cub->map.cub_map = NULL;
	cub->map.floor_color = 0;
	cub->map.ceiling_color = 0;
	cub->key.w = false;
	cub->key.s = false;
	cub->key.a = false;
	cub->key.d = false;
	cub->key.left = false;
	cub->key.right = false;
	cub->no = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->so = NULL;
	cub->map.height = 0;
	cub->map.width = 0;
}

int	main(int argc, char **argv)
{
	t_game	cub;

	init_struct(&cub);
	validate(argc, argv, &cub);
	init(&cub);
	game(&cub);
	bye_bye(&cub, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
