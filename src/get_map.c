/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:25:39 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/17 11:50:02 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	get_map(t_map *map, char *argv)
{
	int	size;
	int	fd;

	fd = open_file(argv);
	size = map_size(fd);
	close(fd);
	allocate_matrix(map, size);
	copy_map(map, argv);
}

int	map_size(int fd)
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
	free(temp);
	return (map_size);
}

void	allocate_matrix(t_map *map, int size)
{
	map->cub_map = ft_calloc(sizeof (char *), size + 1);
	if (!map->cub_map)
	{
		//bye_bye;
		ft_printf("Error: memory allocation failed for map\n");
		exit(EXIT_FAILURE);
	}
}

void	process_map_line(t_map *map, char *temp, int *start)
{
	char	*newline;

	newline = ft_strchr(temp, '\n');
	while (is_space(*temp))
		temp++;
	if (*temp == '1' || *temp == '0')
	{
		if (newline)
			*newline = '\0';
		map->cub_map[(*start)++] = ft_strdup(temp);
	}
}

void	copy_map(t_map *map, char *argv)
{
	int		fd;
	int		start;
	char	*temp;

	fd = open_file(argv);
	start = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		process_map_line(map, temp, &start);
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}



