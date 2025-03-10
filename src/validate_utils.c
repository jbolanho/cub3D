/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:10:45 by anacaro5          #+#    #+#             */
/*   Updated: 2025/03/10 13:51:48 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int open_file(char *argv)
{
	int	file_descriptor;

	file_descriptor = open (argv, O_RDONLY);
	printf("fd: [%d]\n", file_descriptor);
	if (file_descriptor < 0)
	{
		ft_printf("Error: can not open file\n");
		//bye_bye;
		exit (EXIT_FAILURE);
	}
	return (file_descriptor);
}

int	is_space(char c)
{
	if ((c == ' ') || (c == '\t') ||
		(c == '\v') || (c == '\n') || (c == '\r'))
		return (1);
	else
		return (0);
}

uint32_t	convert_rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

