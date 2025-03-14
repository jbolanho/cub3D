/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:57:19 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/14 18:40:37 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	exit_wall_error(char *msg)
{
	//bye_bye;
	ft_printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	check_walls(t_map *map)
{
	int			line;
	int			colum;

	line = 0;
	colum = 0;
	while (map->cub_map[line] != NULL)
		line++;
	while (map->cub_map[0][colum] != '\0')
	{
		if (map->cub_map[0][colum] != '1')
			exit_wall_error("upper wall is open");
		if (map->cub_map[line - 1][colum] != '1')
			exit_wall_error("lower wall is open");
		colum++;
	}
	while (line - 1 != 0)
	{
		if (map->cub_map[line - 1][0] != '1')
			exit_wall_error("left wall is open");
		if (map->cub_map[line - 1][colum - 1] != '1')
			exit_wall_error("right wall is open");
		line--;
	}
}
// void	check_empty_lines(t_map *map)
// {
// 	int	line, col;
// 	int	only_spaces, has_wall;

// 	line = 0;
// 	while (map->cub_map[line] != NULL)
// 	{
// 		only_spaces = 1; // Assume the line has only spaces
// 		has_wall = 0;
// 		col = 0;
// 		while (map->cub_map[line][col] != '\0')
// 		{
// 			if (map->cub_map[line][col] != ' ' && map->cub_map[line][col] != '\t')
// 				only_spaces = 0; // Found a character that is not space or tab
// 			if (map->cub_map[line][col] == '1')
// 				has_wall = 1; // Found a wall
// 			col++;
// 		}
// 		if (only_spaces || (!only_spaces && !has_wall)) // Empty line or no walls
// 		{
// 			ft_printf("Error: empty or invalid line detected at row %d\n", line);
// 			exit(EXIT_FAILURE);
// 		}
// 		line++;
// 	}
// }


