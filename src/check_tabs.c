/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tabs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:24:32 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/17 11:42:57 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	count_tabs(char *line)
{
	int	i;
	int	tab_nbr;

	i = 0;
	tab_nbr = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			tab_nbr++;
		i++;
	}
	return (tab_nbr);
}

char	*replace_tabs(char *line, int tab_nbr)
{
	char	*new_line;
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	new_line = ft_calloc(sizeof(char), ft_strlen(line) + (tab_nbr * 4) + 1);
	while (line[i])
	{
		x = 0;
		if (line[i] == '\t')
		{
			while (x++ < 4)
				new_line[j++] = ' ';
			i++;
			continue ;
		}
		new_line[j++] = line[i++];
	}
	return (new_line);
}

void	check_tabs(t_map *map)
{
	int		i;
	int		tab_nbr;
	char	*new_line;

	i = 0;
	while (map->cub_map[i])
	{
		tab_nbr = count_tabs(map->cub_map[i]);
		if (tab_nbr > 0)
		{
			new_line = replace_tabs(map->cub_map[i], tab_nbr);
			if (!new_line)
			{
                //bye_bye;
				ft_printf("Error: memory allocation failed in tab replacement\n");
				exit(EXIT_FAILURE);
			}
			free(map->cub_map[i]);
			map->cub_map[i] = new_line;
		}
		i++;
	}
}
