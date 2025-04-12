/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:14:52 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/12 16:43:46 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_colors(t_map *map, char *temp)
{
	if (ft_strncmp("F", temp, 1) == 0)
		copy_rgb(&(map->floor_color), temp, map);
	if (ft_strncmp("C", temp, 1) == 0)
		copy_rgb(&(map->ceiling_color), temp, map);
}

void	copy_rgb(uint32_t *color, char *line_cpy, t_map *map)
{
	char	*orig;

	orig = line_cpy;
	if (*color != 0)
	{
		ft_printf("Error: invalid header - duplicated info\n");
		free(line_cpy);
		bye_game(map);
		exit(EXIT_FAILURE);
	}
	line_cpy += 1;
	if (is_space(*line_cpy))
	{
		while (is_space(*line_cpy))
			line_cpy++;
		cut_rgb(color, line_cpy, map);
	}
	else
	{
		ft_printf("Error: invalid color format\n");
		free(orig);
		bye_game(map);
		exit(EXIT_FAILURE);
	}	
}

void	cut_rgb(uint32_t *surface, char *temp, t_map *map)
{
	int		i;
	char	**rgb;

	rgb = cut_rgb_tokens(temp, map);
	*surface = convert_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

char	**cut_rgb_tokens(char *temp, t_map *map)
{
	int		start;
	int		end;
	int		comma;
	char	**rgb;

	start = 0;
	comma = 0;
	rgb = NULL;
	while (temp[start] && is_space(temp[start]))
		start++;
	end = start;
	while (temp[end] && !is_space(temp[end]) && temp[end] != '\n')
		if (temp[end++] == ',')
			comma++;
	if (comma != 2 && comma != 0)
	{
		//free(temp);
		exit_rgb_error(map, temp, "Error: wrong RGB format");
	}
	make_rgb_array(&rgb, temp, map);
	if (!rgb)
		exit_rgb_error(map, temp, "Error: memory allocation failed for RGB array");
	return (rgb);
}

void	make_rgb_array(char ***rgb, char *temp, t_map *map)
{
	int	i;
	int	value;

	i = 0;
	*rgb = ft_split(temp, ',');
	if (!*rgb)
		exit_rgb_error(map, temp, "Error: wrong RGB format");
	while ((*rgb)[i])
	{
		value = ft_atoi((*rgb)[i]);
		if (value < 0 || value > 255)
			exit_rgb_error(map, temp, "Error: not a RGB NUMBER");
		i++;
	}
	if (i != 3)
		exit_rgb_error(map, temp, "Error: bad RGB format");
}
