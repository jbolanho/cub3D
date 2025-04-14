/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.m_check_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:01:46 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/14 18:20:36 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_player(t_map *map)
{
	int	line;
	int	col;
	int	count;

	line = -1;
	count = 0;
	while (map->cub_map[++line])
	{
		col = -1;
		while (map->cub_map[line][++col])
			if (is_player(map->cub_map[line][col], map))
				count_player(map, line, col, &count);
	}
	if (count == 0)
	{
		ft_printf("Error: there is no player\n");
		bye_game(map);
	}
}

int	is_player(char c, t_map *map)
{
	int	pov;

	pov = -1;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (c == 'N')
			pov = N;
		else if (c == 'S')
			pov = S;
		else if (c == 'E')
			pov = E;
		else if (c == 'W')
			pov = W;
		map->player_pov = pov;
	}
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	count_player(t_map *map, int line, int col, int *count)
{
	(*count)++;
	if (*count > 1)
	{
		ft_printf("Error: too many players\n");
		bye_game(map);
	}
	map->player_x = col;
	map->player_y = line;
}

void	check_extra_after_map(t_map *map, char *temp, char *orig, int map_state)
{
	if (map_state == 2)
	{
		ft_printf("Error: extra content after map:%s", temp);
		free(orig);
		bye_game(map);
	}
}

void	check_chr(t_map *map, const char *str)
{
	int			line;
	int			column;

	line = 0;
	while (map->cub_map[line] != NULL)
	{
		column = 0;
		while ((map->cub_map[line])[column] != '\0')
		{
			if (ft_strchr(str, (map->cub_map[line])[column]) == NULL)
			{
				ft_printf("Error: wrong char [%c] on line: %d column: %d\n",
					(map->cub_map[line])[column], line, column);
				bye_game(map);
			}
			column++;
		}
		line++;
	}
}
