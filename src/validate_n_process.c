/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_n_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:09:51 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/14 18:40:52 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	process_argv1(char *argv, t_map *map)
{
	char	*temp;
	int		fd;

	temp = NULL;
	fd = open_file(argv);
	check_header(map, temp, &fd);
	close(fd);
	check_map(map, argv);



	free(temp);
	close(fd);
}

void	check_map(t_map *map, char *argv)
{
	char	*temp;

	temp = NULL;
	get_map(map, argv);
	//9x9???
	check_chr(map, "012NSEW ");
	check_player(map);
	check_walls(map);
	//check_empty_lines(map);
	
}



void	check_header(t_map *map, char *temp, int *fd)
{
	char	*line_cpy;

	temp = get_next_line(*fd);
	while (temp)
	{
		line_cpy = temp;
		while (is_space(*temp))
			temp++;
		check_path(map, temp, line_cpy);
		line_cpy = temp;
		check_colors(map, &(temp[0]), line_cpy);
		//free (line_cpy);
		if (map->north_path && map->south_path && map->west_path && map->east_path && map->floor_color && map->ceiling_color)
			break ;
		printf("map->north_path: %s\n", map->north_path);
		printf("map->south_path: %s\n", map->south_path);
		printf("map->west_path: %s\n", map->west_path);
		printf("map->east_path: %s\n", map->east_path);
		printf("map->floor_color: %u\n", map->floor_color);
		printf("map->ceiling_color: %u\n", map->ceiling_color);
		temp = get_next_line(*fd);
		printf("temp2: %s", temp);
	}
	if (!temp)
	{
		//bye_bye
		ft_printf("Error: invalid map: missing info\n");
		exit(EXIT_FAILURE);
	}
}



