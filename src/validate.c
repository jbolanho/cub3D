/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:13:29 by jbolanho          #+#    #+#             */
/*   Updated: 2025/03/18 14:56:56 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	validate(int argc, char **argv, t_game *cub)
{
	check_argc(argc);
	check_dotcub(argv[1]);
	// printf("AQUIIIII 2");
	process_argv1(argv[1], &cub->map);
	// printf("AQUIIIII   3");
}

void	check_argc(int argc)
{
	if (argc < 2)
	{
		printf("Error: missing map file\n");
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

void	check_dotcub(char *argv)
{
	const char	*extension = "./maps/.cub";
	const char	*extension2 = ".cub";

	if (ft_strlen(argv) <= ft_strlen(extension))
	{
		ft_printf("Error: invalid map format\n");
		//bye_bye;
		exit(EXIT_FAILURE);
	}
	if (strcmp(argv + ft_strlen(argv)
			- ft_strlen(extension2), extension2) != 0)
	{
		ft_printf("Error: file does not end with '.cub'\n");
		//bye_bye;
		exit(EXIT_FAILURE);
	}
}
