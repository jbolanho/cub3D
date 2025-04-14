/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.check_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:09:51 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/14 17:33:32 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*check_header(t_map *map, char *temp, int *fd)
{
	char	*line_cpy;

	temp = get_next_line(*fd);
	while (temp)
	{
		line_cpy = temp;
		while (is_space(*temp))
			temp++;
		check_path(map, temp, line_cpy);
		if (line_cpy != temp)
		{
			temp = ft_strdup(temp);
			free(line_cpy);
		}
		check_colors(map, temp);
		free(temp);
		if (map->north_path && map->south_path && map->west_path
			&& map->east_path && map->floor_color && map->ceiling_color)
		{
			handle_header(*fd, map);
			return (NULL);
		}
		temp = get_next_line(*fd);
	}
	return (temp);
}

void	handle_header(int fd, t_map *map)
{
	char	*temp;

	temp = get_next_line(fd);
	while (temp && (temp[0] != '1' && temp[0] != '0'))
	{
		check_after_header(temp, map);
		free(temp);
		temp = get_next_line(fd);
	}
	if (temp)
		free(temp);
}

void	check_after_header(char *temp, t_map *map)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[0] != '\n' && temp[0] != '\0' && temp[0] != '1'
			&& temp[0] != '0' && temp[0] != ' ')
		{
			ft_printf("Error: BAD info after header\n", temp[i]);
			free(temp);
			bye_game(map);
		}
		i++;
	}
}

void	missing_info(t_map *map)
{
	if (!map->north_path || !map->south_path || !map->west_path
		|| !map->east_path || !map->floor_color || !map->ceiling_color)
	{
		ft_printf("Error: invalid map: missing info\n");
		bye_game(map);
	}
}
