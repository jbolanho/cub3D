/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_n_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:09:51 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/11 14:27:38 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	process_argv1(char *argv, t_map *map)
{
	char	*temp;
	int		fd;

	temp = NULL;
	fd = open_file(argv, map);
	check_header(map, temp, &fd);
	close(fd);
	check_map(map, argv);
	free(temp);
	close(fd);
}

void	check_map(t_map *map, char *argv)
{
	// char	*temp;
	
	// temp = NULL;
	get_map(map, argv);
	check_chr(map, "\t01NSEW ");
	check_walls(map);
	check_space(map, "01NSEW ");
	check_player(map);
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
		check_colors(map, temp);
		free(line_cpy);
		if (map->north_path && map->south_path && map->west_path
			&& map->east_path && map->floor_color && map->ceiling_color)
		{
			handle_header(*fd, map);
			return ;
		}
		temp = get_next_line(*fd);
	}
	ft_printf("Error: invalid map: missing info\n");
	bye_game(map);
	exit(EXIT_FAILURE);
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
			ft_printf("Error: wrong char [%c] found after header\n", temp[i]);
			bye_game(map);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
