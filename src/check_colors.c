/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:14:52 by anacaro5          #+#    #+#             */
/*   Updated: 2025/02/25 18:42:56 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_colors(t_map *map, char *temp)
{
	if (ft_strncmp("F", temp, 1) == 0)
		copy_rgb(&(map->floor_color), temp, "F");
	else if (ft_strncmp("C", temp, 2) == 0)
		copy_rgb(&(map->ceiling_color), temp, "C");
	else
	{
		if (temp[0] != '\n' && temp[0] != '\0')
		{
			//bye_bye;
			ft_printf("Error: invalid char on header\n");
			exit (EXIT_FAILURE);
		}
	}
}

void	copy_rgb(uint32_t *color, char *temp, char *info)
{
	(void) info;
	if (color != NULL)
	{
		//bye_bye;
		ft_printf("Error: invalid header - duplicated info\n");
		exit(EXIT_FAILURE);
	}
	temp += 1;
	if (is_space(*temp))
	{
		while (is_space(*temp))
			temp++;
		cut_rgb(color, temp);
	}
	else
	{
		//bye_bye;
 		ft_printf("Error: invalid color format\n");
		exit(EXIT_FAILURE);
	}	
}

void	cut_rgb(uint32_t surface, char *temp)
{
	int	start;
	int	end;
	int	i;
	int comma;
    char **rgb;

	start = 0;
	while (temp[start] && is_space(temp[start]))
		start++;
	end = start;
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
    make_rgb_array(&rgb, temp[start], ascii);
    *surface = (convert_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2])));
    
}


void    make_rgb_array(char ***rgb, char *temp)
{
    int i;
    
    i = 0;
    *rgb = ft_split(*temp, ',');
    if (!*rgb)
    {
		//bye_bye;
		ft_printf("Error: wrong RGB format\n");
		exit(EXIT_FAILURE);
	}
    while ((*rgb)[i])
    {
        if ((*rgb)[i] < 0 && (*rgb)[i] > 255)
        {
		    //bye_bye;
		    ft_printf("Error: not a RGB NUMBER\n");
		    exit(EXIT_FAILURE);
	    }
        if (i != 3)
        {
		    //bye_bye;
		    ft_printf("Error: bad RGB format\n");
		    exit(EXIT_FAILURE);
	    }
    }
}