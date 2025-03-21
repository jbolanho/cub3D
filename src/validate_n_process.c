/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_n_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:09:51 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/21 19:22:27 by anacaro5         ###   ########.fr       */
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
	// printf("AQUIIIII 4\n");
}

void	check_map(t_map *map, char *argv)
{
	char	*temp;

	temp = NULL;
	get_map(map, argv);
	//check_tabs(map);
	check_chr(map, "\t01NSEW ");
	check_walls(map);
	check_space(map, "01NSEW");
	check_player(map);
	//check_empty_lines(map);
	
}



void	check_header(t_map *map, char *temp, int *fd)
{
	char	*line_cpy;
	//int 	i;

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
		{
			temp = get_next_line(*fd);
			while (temp[0] != '1' && temp[0] != '0')
			{
				check_after_header(temp);
				temp = get_next_line(*fd);
			}
			free(temp);
			break ;
		}
		//CONTINUAR CHECKANDO
			// printf("map->north_path: %s\n", map->north_path);
		// printf("map->south_path: %s\n", map->south_path);
		// printf("map->west_path: %s\n", map->west_path);
		// printf("map->east_path: %s\n", map->east_path);
		// printf("map->floor_color: %u\n", map->floor_color);
		// printf("map->ceiling_color: %u\n", map->ceiling_color);
		// i = 0;
		// while (temp[i])
		// {
		// 	if (ft_strchr("012NSEW ", temp[i]) == NULL)
		// 	{
		// 		//bye_bye;
		// 		ft_printf("Error: wrong char [%c]\n"
		// 			"found\n", temp[i]);
		// 		exit(EXIT_FAILURE);
		// 	}
		// 	i++;
		// }
		//free(temp);
		temp = get_next_line(*fd);
	}
	if (!temp)
	{
		//bye_bye
		ft_printf("Error: invalid map: missing info\n");
		exit(EXIT_FAILURE);
	}
}

void	check_after_header(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[0] != '\n' && temp[0] != '\0' && temp[0] != '1' && temp[0] != '0' && temp[0] != '\t' && temp[0] != ' ')
		{
			//bye_bye;
			ft_printf("Error: wrong char [%c] found\n", temp[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
