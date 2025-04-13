/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:10:45 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/12 17:33:27 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	is_space(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\v')
		|| (c == '\n') || (c == '\r'))
		return (1);
	else
		return (0);
}

uint32_t	convert_rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	allocate_matrix(t_map *map, int size)
{
	printf("Sieze: %d\n", size);
	printf("map->height: %d\n", map->height);
	map->cub_map = ft_calloc(sizeof (char *), size + 1);
	if (!map->cub_map)
	{
		ft_printf("Error: memory allocation failed for map\n");
		bye_game(map);
		exit(EXIT_FAILURE);
	}
}

void	print_map(t_map *map)
{
	int	i;

	if (!map || !map->cub_map)
	{
		printf("Error: map is NULL\n");
		return ;
	}
	i = 0;
	printf("==== Mapa Carregado ====\n");
	while (map->cub_map[i])
	{
		printf("%s\n", map->cub_map[i]);
		i++;
	}
	printf("========================\n");
}


