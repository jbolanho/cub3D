/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:25:39 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/11 15:00:43 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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
	invalid_char(map, temp, start, map_state);
}

void	check_extra_after_map(t_map *map, char *temp, char *orig, int map_state)
{
	if (map_state == 2)
	{
		ft_printf("Error: Extra content after map: \"%s\"\n", temp);
		free(orig);
		bye_game(map);
		exit(EXIT_FAILURE);
	}
}

void	invalid_char(t_map *map, char *temp, int *start, int *map_state)
{
	char	*ptr;

	ptr = temp;
	while (*ptr)
	{
		if (!ft_strchr(" \t01NSEW\n", *ptr) && *map_state == 1)
		{
			ft_printf("Error: Invalid chr\n'%c' on line [%d] and column [%d].\n",
				*ptr, *start, (int)(ptr - temp));
			free(temp);
			bye_game(map);
			exit(EXIT_FAILURE);
		}
		ptr++;
	}
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
