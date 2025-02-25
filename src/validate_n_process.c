/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_n_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:09:51 by anacaro5          #+#    #+#             */
/*   Updated: 2025/02/25 18:40:12 by anacaro5         ###   ########.fr       */
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

}

void	check_header(t_map *map, char *temp, int *fd)
{
	char	*line_cpy;

	temp = get_next_line(*fd); //copia uma linha, para ser verificada
	while (temp)
	{
		line_cpy = temp;
		while (is_space(*temp))  //pula se tiver espaços
			temp++;
		check_path(map, temp, line_cpy);  //verifica se tem caminho para as txt naquela linha e já salva; e se há linha inválida
		free (line_cpy);
		//check_colors(map, &(temp[0]));
		if (map->north_path && map->south_path && map->west_path && map->east_path && map->floor_color && map->ceiling_color)
			break ;
		temp = get_next_line(*fd);
		printf("temp: [%s]\n", temp);
	}
	printf("temp: [%s]\n", temp);
	if (!temp)
	{
		//bye_bye
		ft_printf("Error: invalid map: missing info\n");
		exit(EXIT_FAILURE);
	}
}

