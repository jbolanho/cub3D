/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:19:33 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/14 17:55:44 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"


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
				//bye_bye;
				ft_printf("Error: wrong char [%c]\n"
					"found on line: %d, columnn: %d\n",
					(map->cub_map[line])[column], line, column);
				exit(EXIT_FAILURE);
			}
			column++;
		}
		line++;
	}
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	count_player(t_map *map, int line, int col, int *count)
{
	(*count)++;
	if (*count > 1)
	{
		//bye_bye;
		ft_printf("Error: too many players\n");
		exit(EXIT_FAILURE);
	}
	map->player_x = line;
	map->player_y = col;
}

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
			if (is_player(map->cub_map[line][col]))
				count_player(map, line, col, &count);
	}
	if (count == 0)
	{
		//bye_bye;
		ft_printf("Error: there is no player\n");
		exit(EXIT_FAILURE);
	}
}



