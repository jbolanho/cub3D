/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.m_check_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:57:19 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/14 17:24:33 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_walls(t_map *map)
{
	int	line;
	int	column;

	line = 0;
	while (map->cub_map[line])
	{
		column = 0;
		while (map->cub_map[line][column])
		{
			check_wall_surroundings(map, line, column);
			column++;
			if (column > map->width)
				map->width = column;
		}
		line++;
	}
}

void	check_wall_surroundings(t_map *map, int y, int x)
{
	char	c;

	c = safe_map_get(map, y, x);
	if (!is_player_or_space(c))
		return ;
	if (safe_map_get(map, y - 1, x) == ' ' || safe_map_get(map, y + 1, x) == ' '
		|| safe_map_get(map, y, x - 1) == ' '
		|| safe_map_get(map, y, x + 1) == ' ')
		print_wall_error(y, x, map);
}

char	safe_map_get(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(map->cub_map[y]))
		return (' ');
	return (map->cub_map[y][x]);
}

int	is_player_or_space(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	print_wall_error(int line, int column, t_map *map)
{
	ft_printf("Error: open wall on line: %d column: %d\n", line, column);
	bye_game(map);
}
