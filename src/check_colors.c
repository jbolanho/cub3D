/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:14:52 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/11 17:23:55 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_colors(t_map *map, char *temp, char *line_cpy)
{
	printf("temp: %s\n", temp);
	if (ft_strncmp("F", temp, 1) == 0)
	{
		printf("temp dentro do if: %s\n", temp);
		printf("line_cpy dentro do if: %s\n", line_cpy);
		printf("floor1: %d\n", map->floor_color);
		copy_rgb(&(map->floor_color), line_cpy);
		printf("floor2: %d\n", map->floor_color);
	}
	if (ft_strncmp("C", temp, 1) == 0)
	{
		printf("temp dentro do if: %s\n", temp);
		printf("line_cpy dentro do if: %s\n", line_cpy);
		printf("ceiling: %d\n", map->ceiling_color);
		copy_rgb(&(map->ceiling_color), line_cpy);
	}
	// printf("floor: %d\n", map->floor_color);
	// printf("ceiling: %d\n", map->ceiling_color);
	// printf("temp: %s\n", temp);
	// printf("temp[0]: %c\n", temp[0]);

}

void	copy_rgb(uint32_t *color, char *line_cpy)
{
	printf("color: %d\n", *color);
	if (*color != 0)
	{
		//bye_bye;
		ft_printf("Error: invalid header - duplicated info\n");
		exit(EXIT_FAILURE);
	}
	line_cpy += 1;
	if (is_space(*line_cpy))
	{
		while (is_space(*line_cpy))
			line_cpy++;
		printf("line_cpy: %s\n", line_cpy);
		cut_rgb(color, line_cpy);
	}
	else
	{
		//bye_bye;
 		ft_printf("Error: invalid color format\n");
		exit(EXIT_FAILURE);
	}	
}

void	cut_rgb(uint32_t *surface, char *temp)
{
	int		start;
	int		end;
	int		comma;
	char	**rgb;

	rgb = NULL;
	start = 0;
	printf("temp: %s\n", temp);
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
	if (comma != 2)
	{
		//bye_bye;
		ft_printf("Error: wrong RGB format\n");
		exit(EXIT_FAILURE);
	}
	// printf("rgb[0]: %s\n", rgb[0]);
	// printf("rgb[1]: %s\n", rgb[1]);
	// printf("rgb[2]: %s\n", rgb[2]);
	// printf("temp: %s\n", temp);
	make_rgb_array(&rgb, temp);
	printf("rgb[0]: %s\n", rgb[0]);
	if (!rgb) // Verifica se o ponteiro foi alocado corretamente
	{
    	ft_printf("Error: memory allocation failed for RGB array\n");
    	exit(EXIT_FAILURE);
	}
	*surface = (convert_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2])));
	printf("surface: %d\n", *surface);
	comma = 0;
	while (rgb[comma])
	{
		free(rgb[comma]);
		comma++;
	}
	free(rgb);
}


void	make_rgb_array(char ***rgb, char *temp)
{
	int	i;
	int	value;

	*rgb = ft_split(temp, ',');
	printf("rgb[0]: %s\n", *rgb[0]);
	if (!*rgb)
	{
		//bye_bye;
		ft_printf("Error: wrong RGB format\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (((*rgb)[i]))
	{
		value = ft_atoi((*rgb)[i]);
		if (value < 0 || value > 255)
		{
			//bye_bye;
			ft_printf("Error: not a RGB NUMBER\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (i != 3)
	{
		//bye_bye;
		ft_printf("Error: bad RGB format\n");
		exit(EXIT_FAILURE);
	}
}

