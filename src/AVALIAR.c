/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVALIAR.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:19:33 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/12 17:33:18 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"



// void	check_empty_lines(char **temp)
// {
// 	int	line;

// 	line = 0;
// 	while (temp[line] != NULL)
// 	{
// 		if (temp[line] == NULL || ft_strlen(temp[line]) == 0)
// 		{
// 			ft_printf("Error: empty line found at line: %d\n", line);
// 			exit(EXIT_FAILURE);
// 		}
// 		line++;
// 	}
// }

// void	invalid_char(t_map *map, char *temp, int *start, int *map_state)
// {
// 	char	*ptr;

// 	ptr = temp;
// 	while (*ptr)
// 	{
// 		if (!ft_strchr(" \t01NSEW\n", *ptr) && *map_state == 1)
// 		{
// 			ft_printf("Error: Invalid chr '%c' on line [%d] and column [%d].\n",
// 				*ptr, *start, (int)(ptr - temp));
// 			free(temp);
// 			ptr = NULL;
// 			bye_game(map);
// 			exit(EXIT_FAILURE);
// 		}
// 		ptr++;
// 	}
// }


// void	check_chr(t_map *map, const char *str)
// {
// 	int			line;
// 	int			column;

// 	line = 0;
// 	while (map->cub_map[line] != NULL)
// 	{
// 		column = 0;
// 		while ((map->cub_map[line])[column] != '\0')
// 		{
// 			if (ft_strchr(str, (map->cub_map[line])[column]) == NULL)
// 			{
// 				ft_printf("Error: wrong char [%c] on line: %d column: %d\n",
// 					(map->cub_map[line])[column], line, column);
// 				bye_game(map);
// 				exit(EXIT_FAILURE);
// 			}
// 			column++;
// 		}
// 		line++;
// 	}
// }

// void	check_space(t_map *map, const char *str)
// {
// 	int			line;
// 	int			column;

// 	line = 0;
// 	while (map->cub_map[line] != NULL)
// 	{
// 		column = 0;
// 		while (map->cub_map[line][column] != '\0')
// 		{
// 			if (column == 0)
// 				column++;
// 			if (ft_strchr(str, (map->cub_map[line])[column]) == NULL)
// 			{
// 				ft_printf("Error: found space or tab [%c]\n"
// 					"on line: %d, columnn: %d\n",
// 					(map->cub_map[line])[column], line, column);
// 				bye_game(map);
// 				exit(EXIT_FAILURE);
// 			}
// 			column++;
// 		}
// 		line++;
// 	}
// }



