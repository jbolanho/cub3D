/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:12:51 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/10 13:17:29 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void check_path(t_map *map, char *temp, char *line_cpy)
{
	if (ft_strncmp("NO", temp, 2) == 0)
		copy_path(&(map->north_path), temp, "NO", line_cpy);
	else if (ft_strncmp("SO", temp, 2) == 0)
		copy_path(&(map->south_path), temp, "SO", line_cpy);
	else if (ft_strncmp("WE", temp, 2) == 0)
		copy_path(&(map->west_path), temp, "WE", line_cpy);
	else if (ft_strncmp("EA", temp, 2) == 0)
		copy_path(&(map->east_path), temp, "EA", line_cpy);
	else
	{
		if (temp[0] != '\n' && temp[0] != '\0' && temp[0] != 'F' && temp[0] != 'C' && temp[0] != '1')
		{
			free (line_cpy);
			//bye_bye;
			ft_printf("Error: invalid char on header\n");
			exit (EXIT_FAILURE);
		}
	}
	//F e C
	//colors
	//qt de texturas?
}

void	copy_path(char **texture, char *temp, char *info, char *line_cpy)
{
	(void) info;
	if (*texture != NULL)
	{
		free(line_cpy);
		//bye_bye;
		ft_printf("Error: invalid header - duplicated info\n");
		exit(EXIT_FAILURE);
	}
	temp +=2;
	if (is_space(*temp))
	{
		while (is_space(*temp))
			temp++;
		cut_path(temp, line_cpy, texture);
	}
	else
	{
		free(line_cpy);
		//bye_bye;
 		ft_printf("Error: invalid texture path\n");
		exit(EXIT_FAILURE);
	}	
}

void	cut_path(char *temp, char *line_cpy, char **texture)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	while (temp[start] && is_space(temp[start]))
		start++;
	end = start;
	while (temp[end] && !is_space(temp[end]) && temp[end] != '\n')
		end++;
	after_path(&temp[end], line_cpy);
	*texture = (char *)malloc((end - start + 1) * sizeof(char));
	if (!*texture)
	{
		free(line_cpy);
		//bye_bye;
		ft_printf("Error: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (start < end)
		(*texture)[i++] = temp[start++];
	(*texture)[i] = '\0';
}

void	after_path(char *temp, char *line_cpy)
{
	char	*after;

	after = temp;
	while (*after)
	{
		if (!is_space(*after) && *after != '\n')
		{
			free(line_cpy);
			//bye_bye;
 			ft_printf("Error: invalid char after path\n");
			exit(EXIT_FAILURE);
		}
		after += 1;
	}
}