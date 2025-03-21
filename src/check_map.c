/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:19:33 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/21 18:55:45 by anacaro5         ###   ########.fr       */
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

void	check_space(t_map *map, const char *str)
{
	int			line;
	int			column;

	line = 0;
	while (map->cub_map[line] != NULL)
	{
		column = 0;
		while (map->cub_map[line][column] != '\0')
		{
			if (column == 0)
				column++;
			// if (is_space(map->cub_map[line][column]) == 1)
			// {
			// 	printf("aquiii\n");
			// 	column++;
			// }
			if (ft_strchr(str, (map->cub_map[line])[column]) == NULL)
			{
				//bye_bye;
				ft_printf("Error: found space or tab [%c]\n"
					"on line: %d, columnn: %d\n",
					(map->cub_map[line])[column], line, column);
				exit(EXIT_FAILURE);
			}
			column++;
		}
		line++;
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
		// printf("AQUII: pov: %d\n", pov);		
		map->player_pov = pov;
		// printf("AQUII:map->player_pov: %d\n", map->player_pov);
	}	

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
	map->player_x = col;
	map->player_y = line;
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
			if (is_player(map->cub_map[line][col], map))
				count_player(map, line, col, &count);
	}
	if (count == 0)
	{
		//bye_bye;
		ft_printf("Error: there is no player\n");
		exit(EXIT_FAILURE);
	}
}



