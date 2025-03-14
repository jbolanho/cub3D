/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byebye.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:14:36 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/14 18:15:46 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_matrix(t_map *map)
{
	int	row;

	row = 0;
	while (map->cub_map[row] != NULL)
	{
		free(map->cub_map[row]);
		row++;
	}
	free(map->cub_map);
}

