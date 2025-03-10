/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:25:39 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/10 17:23:49 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_size(t_map *map, char *temp, char *argv)
{
	int	map_size;
	int	fd;

	map_size = 0;
	fd = open_file(argv);
	temp = get_next_line(fd);
	while (temp)
	{
		map_size++;
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
	map->cub_map = calloc(sizeof (char *), map_size + 1);
	if (!map->cub_map)
	{
		//bye_bye;
		ft_printf("Error: memory allocation failed for map\n");
		exit(EXIT_FAILURE);
	}
	map->hei = map_size;
	printf("hei_size: %d\n", map->hei);
}
