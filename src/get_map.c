/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:25:39 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/10 17:26:28 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	process_map_line(t_map *map, char *temp, int *start, int *map_state)
{
	char	*newline;
	int		count;
	char	*ptr;

	newline = ft_strchr(temp, '\n');
	count = 0;
	while (is_space(*temp))
	{
		count += 1;
		temp++;
	}
	if (ft_strncmp(temp, "NO ", 3) == 0 || ft_strncmp(temp, "SO ", 3) == 0
		|| ft_strncmp(temp, "EA ", 3) == 0 || ft_strncmp(temp, "WE ", 3) == 0
		|| ft_strncmp(temp, "F ", 2) == 0 || ft_strncmp(temp, "C ", 2) == 0)
		{
			*map_state = 1;
			return ;
		}
	else
	{
		while (count > 0)
		{
			temp--;
			count--;
		}
	}
	printf("temp dentro do process: '%s'\n", temp);
	
	///////////////////////////////////////////////////////////////////////////
	if (*map_state == 3)
	{
		ft_printf("Error: Invalid map. Extra content found after map.\n");
		bye_game(map);
		exit(EXIT_FAILURE);
	}
	// if (*map_state == 2 && (temp[0] == '1' || temp[0] == '0'))
	// {
	// 	ft_printf("Error: MAP found after header\n");
	// 	bye_game(map);
	// 	exit(EXIT_FAILURE);
	// }
	if ((*temp == '1' || *temp == '0' || *temp == ' ' || *temp == '\t'
		|| *temp == 'N' || *temp == 'S' || *temp == 'E' || *temp == 'W' || *temp == '\n') && (*map_state > 0))
	{
		printf("map_state: %d\n", *map_state);
		printf("ENTROU");
		*map_state = 2;
		if (newline)
			*newline = '\0';
		map->cub_map[(*start)++] = ft_strdup(temp);
		// if (*map_state == 2)
		// {
		// 	ft_printf("Error: Invalid map. Extra content found after map.\n");
		// 	bye_game(map);
		// 	exit(EXIT_FAILURE);
		// }
		printf("temp: %s\n", temp);
		while (temp)
		{
			printf("temp2: %s\n", temp);
			while (is_space(*temp))
				temp++;
			if (*temp == '\0')
			{
				*map_state = 3;
				break ;
			}
			else 
				break ;
		// if (*map_state == 2)
		// {
		// 	ft_printf("Error: Invalid map. Extra content found after map.\n");
		// 	bye_game(map);
		// 	exit(EXIT_FAILURE);
		// }
		}
	}
	ptr = temp;
	//print_map(map);
	while (*ptr)
	{
		if (!ft_strchr(" \t01NSEW\n", *ptr) && *map_state == 1)
		{
			ft_printf("Error: Invalid chr\n'%c' on line [%d] and column [%d].\n",
				*ptr, *start, (int)(ptr - temp));
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
		printf("Temp aqui é: %s\n", temp);
		process_map_line(map, temp, &start, &map_state);
		free(temp);
		temp = get_next_line(fd);
		
	}
	close(fd);
	print_map(map);
}

void	print_map(t_map *map)
{
	int	i;

	if (!map || !map->cub_map)
	{
		printf("Error: map is NULL\n");
		return ;
	}
	i = 0;
	printf("==== Mapa Carregado ====\n");
	while (map->cub_map[i])
	{
		printf("%s\n", map->cub_map[i]);
		i++;
	}
	printf("========================\n");
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
	free(temp);
	map->height = map_size;
	return (map_size);
}

void	allocate_matrix(t_map *map, int size)
{
	map->cub_map = ft_calloc(sizeof (char *), size + 1);
	if (!map->cub_map)
	{
		ft_printf("Error: memory allocation failed for map\n");
		bye_game(map);
		exit(EXIT_FAILURE);
	}
}

// void	process_map_line(t_map *map, char *temp, int *start)
// {
// 	char	*newline;

// 	newline = ft_strchr(temp, '\n');
// 	while (is_space(*temp))
// 		temp++;
// 	if (*temp == '1' || *temp == '0')
// 	{
// 		if (newline)
// 			*newline = '\0';
// 		map->cub_map[(*start)++] = ft_strdup(temp);
// 	}
// }

// void	copy_map(t_map *map, char *argv)
// {
// 	int		fd;
// 	int		start;
// 	char	*temp;

// 	fd = open_file(argv);
// 	start = 0;
// 	temp = get_next_line(fd);
// 	while (temp)
// 	{
// 		process_map_line(map, temp, &start);
// 		free(temp);
// 		temp = get_next_line(fd);
// 	}
// 	close(fd);
// }
