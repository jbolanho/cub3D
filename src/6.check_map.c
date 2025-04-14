/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.check_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:25:39 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/14 17:12:30 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_map(t_map *map, char *argv)
{
	get_map(map, argv);
	check_chr(map, "\t01NSEW ");
	check_walls(map);
	check_player(map);
}

void	get_map(t_map *map, char *argv)
{
	int	size;
	int	fd;

	fd = open_file(argv, map);
	size = map_size(fd, map);
	close(fd);
	allocate_matrix(map, size);
	copy_map(map, argv);
}

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
		while (is_space(temp[i]))
			i++;
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

void	copy_map(t_map *map, char *argv)
{
	int		fd;
	int		start;
	char	*temp;
	int		map_state;

	fd = open_file(argv, map);
	start = 0;
	map_state = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		process_map_line(map, temp, &start, &map_state);
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}

void	process_map_line(t_map *map, char *temp, int *start, int *map_state)
{
	char	*newline;
	char	*orig;

	newline = ft_strchr(temp, '\n');
	orig = temp;
	while (is_space(*temp))
		temp++;
	if (ft_strncmp(temp, "NO ", 3) == 0 || ft_strncmp(temp, "SO ", 3) == 0
		|| ft_strncmp(temp, "EA ", 3) == 0 || ft_strncmp(temp, "WE ", 3) == 0
		|| ft_strncmp(temp, "F ", 2) == 0 || ft_strncmp(temp, "C ", 2) == 0)
		return ;
	if (*temp == '\0')
	{
		if (*map_state == 1)
			*map_state = 2;
		return ;
	}
	check_extra_after_map(map, temp, orig, *map_state);
	if (*map_state == 0)
		*map_state = 1;
	if (newline)
		*newline = '\0';
	map->cub_map[(*start)++] = ft_strdup(temp);
}
