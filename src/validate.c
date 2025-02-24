/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:13:29 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/24 16:16:46 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	validate(int argc, char **argv, t_game *cub)
{
	check_argc(argc);
	check_dotcub(argv[1]);
	process_argv1(argv[1], cub->map);
}

void	check_argc(int argc)
{
	if (argc < 2)
	{
		printf("Error: missing map file");
		//bye_bye;
		exit(EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		printf("Error: too many arguments\n");
		//bye_bye;
		exit(EXIT_FAILURE);
	}
}

void	check_dotcub(char **argv)
{
	const char	*extension = ".cub";

	if (ft_strlen(argv[1]) <= ft_strlen(extension))
	{
		ft_printf("Error: invalid map format\n");
		//bye_bye;
		exit(EXIT_FAILURE);
	}
	if (strcmp(argv[1] + ft_strlen(argv[1])
			- ft_strlen(extension), extension) != 0)
	{
		ft_printf("Error: file does not end with '.cub'\n");
		//bye_bye;
		exit(EXIT_FAILURE);
	}
}
