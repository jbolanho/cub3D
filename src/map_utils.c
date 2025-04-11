/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:01:46 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/11 15:27:23 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	map_size(int fd, t_map *map)
{
	int		map_size;
	char	*temp;
	int		i;

	map_size = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		i = 0;
		if (is_space(temp[i]))
			i++;
		printf("temp[%d]: %c\n", i, temp[i]);
		if (temp[i] == '1' || temp[i] == '0')
			break ;
		free(temp);
		temp = get_next_line(fd);
	}
	while (temp)
	{
		map_size++;
		free(temp);
		temp = get_next_line(fd);
	}
	map->height = map_size;
	return (map_size);
}

void	check_empty_lines(char **temp)
{
	int	line;

	line = 0;
	while (temp[line] != NULL)
	{
		if (temp[line] == NULL || ft_strlen(temp[line]) == 0)
		{
			ft_printf("Error: empty line found at line: %d\n", line);
			exit(EXIT_FAILURE);
		}
		line++;
	}
}
