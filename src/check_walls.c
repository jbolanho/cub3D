/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:57:19 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/21 19:57:19 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// void	exit_wall_error(char *msg)
// {
// 	//bye_bye;
// 	ft_printf("Error: %s\n", msg);
// 	exit(EXIT_FAILURE);
// }

// void	check_walls(t_map *map)
// {
// 	int			line;
// 	int			colum;

// 	line = 0;
// 	colum = 0;
// 	while (map->cub_map[line] != NULL)
// 		line++;
// 	while (map->cub_map[0][colum] != '\0')
// 	{
// 		if (map->cub_map[0][colum] != '1')
// 			exit_wall_error("upper wall is open");
// 		if (map->cub_map[line - 1][colum] != '1')
// 			exit_wall_error("lower wall is open");
// 		colum++;
// 	}
// 	while (line - 1 != 0)
// 	{
// 		if (map->cub_map[line - 1][0] != '1')
// 			exit_wall_error("left wall is open");
// 		if (map->cub_map[line - 1][colum - 1] != '1')
// 			exit_wall_error("right wall is open");
// 		line--;
// 	}
// }


// void	check_walls(t_map *map)
// {
// 	int			line;
// 	int			column;

// 	line = 0;
// 	while (map->cub_map[line] != NULL)
// 	{
// 		column = 0;
// 		while (map->cub_map[line][column] != '\0')
// 		{
// 			if (map->cub_map[line][column] == '0' && column == 0)
// 			{
// 				ft_printf("Error: open wall on line: %d, column: %d\n",
// 				line, column);
// 				exit(EXIT_FAILURE);
// 			}
// 			if (map->cub_map[line][column] == '0' && 
// 				(column == 0 || map->cub_map[line][column + 1] == '\0'))
// 			{
// 				ft_printf("Error: open wall on line: %d, column: %d\n",
// 				line, column);
// 				exit(EXIT_FAILURE);
// 			}
// 			if (map->cub_map[line][column] == '0' || map->cub_map[line][column] == 'N' || 
// 				map->cub_map[line][column] == 'S' || map->cub_map[line][column] == 'E' || 
// 				map->cub_map[line][column] == 'W')
// 			{
// 				if (line == 0 || map->cub_map[line + 1] == NULL || 
// 					column == 0 || map->cub_map[line][column + 1] == '\0' || 
// 					map->cub_map[line - 1][column] == ' ' || map->cub_map[line + 1][column] == ' ' || 
// 					map->cub_map[line][column - 1] == ' ' || map->cub_map[line][column + 1] == ' ')
// 				{
// 					ft_printf("Error: open wall on line: %d, column: %d\n",
// 					line, column);
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 			column++;
// 		}
// 		line++;
// 	}
// }

void	print_wall_error(int line, int column)
{
	ft_printf("Error: open wall on line: %d, column: %d\n", line, column);
	exit(EXIT_FAILURE);
}

int	is_player_or_space(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	check_wall_edges(t_map *map, int line, int column)
{
	if (map->cub_map[line][column] == '0' &&
		(column == 0 || map->cub_map[line][column + 1] == '\0'))
		print_wall_error(line, column);
}

void	check_wall_surroundings(t_map *map, int line, int column)
{
	if (!is_player_or_space(map->cub_map[line][column]))
		return;
	if (line == 0 || map->cub_map[line + 1] == NULL ||
		column == 0 || map->cub_map[line][column + 1] == '\0' ||
		map->cub_map[line - 1][column] == ' ' ||
		map->cub_map[line + 1][column] == ' ' ||
		map->cub_map[line][column - 1] == ' ' ||
		map->cub_map[line][column + 1] == ' ')
		print_wall_error(line, column);
}

void	check_all_walls(t_map *map, int line, int column)
{
	check_wall_edges(map, line, column);
	check_wall_surroundings(map, line, column);
}

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
			check_all_walls(map, line, column);
			column++;
		}
		line++;
	}
}
