/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:24:55 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/11 12:35:26 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void    init(t_game *cub, int argc, char **argv)
{
    (void)cub;
    (void)argc;
    (void)argv;
    cub->map.north_path = NULL;
	cub->map.south_path = NULL;
	cub->map.east_path = NULL;
	cub->map.west_path = NULL;
	cub->map.floor_color = 0;
	cub->map.ceiling_color = 0;
}