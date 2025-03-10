/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_n_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:09:51 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/10 17:24:49 by anacaro5         ###   ########.fr       */
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
	printf("temp: %s\n", temp);
	close(fd);
	//fd = open_file(argv);
	check_size(map, temp, argv);


	free(temp);
	close(fd);
}
// void	check_map(t_map *map, char *temp, int *fd)
// {
// 	check_size(map, temp, argv);
// }
void	check_header(t_map *map, char *temp, int *fd)
{
	char	*line_cpy;

	temp = get_next_line(*fd);
	//map->hei = 0;
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
		//map->hei++;
		temp = get_next_line(*fd);
	}
	//printf("hei: %d\n", map->hei);
	if (!temp)
	{
		//bye_bye
		ft_printf("Error: invalid map: missing info\n");
		exit(EXIT_FAILURE);
	}
}

