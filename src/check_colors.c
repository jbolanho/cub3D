/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:14:52 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/08 14:55:51 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_colors(t_map *map, char *temp)
{
	if (ft_strncmp("F", temp, 1) == 0)
	{
		// printf("temp dentro do if: %s\n", temp);
		// printf("line_cpy dentro do if: %s\n", line_cpy);
		// printf("floor1: %d\n", map->floor_color);
		copy_rgb(&(map->floor_color), temp, map);
		// printf("floor2: %d\n", map->floor_color);
	}
	if (ft_strncmp("C", temp, 1) == 0)
	{
		// printf("temp dentro do if: %s\n", temp);
		// printf("line_cpy dentro do if: %s\n", line_cpy);
		// printf("ceiling: %d\n", map->ceiling_color);
		copy_rgb(&(map->ceiling_color), temp, map);
	}
}

void	copy_rgb(uint32_t *color, char *line_cpy, t_map *map)
{
	//printf("color: %d\n", *color);
	if (*color != 0)
	{
		ft_printf("Error: invalid header - duplicated info\n");
		bye_game(map);
		exit(EXIT_FAILURE);
	}
	line_cpy += 1;
	if (is_space(*line_cpy))
	{
		while (is_space(*line_cpy))
			line_cpy++;
		//printf("line_cpy: %s\n", line_cpy);
		cut_rgb(color, line_cpy, map);
	}
	else
	{
		ft_printf("Error: invalid color format\n");
		bye_game(map);
		exit(EXIT_FAILURE);
	}	
}

void	cut_rgb(uint32_t *surface, char *temp, t_map *map)
{
	int		start;
	int		end;
	int		comma;
	char	**rgb;

	rgb = NULL;
	start = 0;
	//printf("temp: %s\n", temp);
	while (temp[start] && is_space(temp[start]))
		start++;
	end = start;
	comma = 0;
	while (temp[end] && !is_space(temp[end]) && temp[end] != '\n')
	{
		if (temp[end] == ',')
			comma++;
		end++;
	}
	//printf("virgulaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa: %d", comma);
	if (comma != 2 && comma != 0)
	{
		ft_printf("Error: wrong RGB format\n");
		bye_game(map);
		exit(EXIT_FAILURE);
	}
	make_rgb_array(&rgb, temp, map);
	if (!rgb)
	{
		ft_printf("Error: memory allocation failed for RGB array\n");
		bye_game(map);
		exit(EXIT_FAILURE);
	}
	*surface = (convert_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2])));
	comma = 0;
	while (rgb[comma])
	{
		free(rgb[comma]);
		comma++;
	}
	free(rgb);
}

void	make_rgb_array(char ***rgb, char *temp, t_map *map)
{
	int	i;
	int	value;

	*rgb = ft_split(temp, ',');
	//printf("rgb[0]: %s\n", *rgb[0]);
	if (!*rgb)
	{
		ft_printf("Error: wrong RGB format\n");
		bye_game(map);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (((*rgb)[i]))
	{
		value = ft_atoi((*rgb)[i]);
		if (value < 0 || value > 255)
		{
			ft_printf("Error: not a RGB NUMBER\n");
			bye_game(map);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (i != 3)
	{
		ft_printf("Error: bad RGB format\n");
		bye_game(map);
		exit(EXIT_FAILURE);
	}
}
