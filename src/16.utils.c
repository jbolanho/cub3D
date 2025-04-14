/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16.utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:10:45 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/14 18:22:49 by jbolanho         ###   ########.fr       */
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
	map->cub_map = ft_calloc(sizeof (char *), size + 1);
	if (!map->cub_map)
	{
		ft_printf("Error: memory allocation failed for map\n");
		bye_game(map);
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

void	exit_rgb_error(t_map *map, char *temp, char *orig, const char *msg)
{
	ft_printf("%s :%s", msg, temp);
	free(orig);
	free(temp);
	bye_game(map);
}
