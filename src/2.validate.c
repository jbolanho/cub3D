/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.validate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:13:29 by jbolanho          #+#    #+#             */
/*   Updated: 2025/04/14 17:48:06 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	validate(int argc, char **argv, t_game *cub)
{
	check_argc(argc, &cub->map);
	check_dotcub(argv[1], &cub->map);
	process_argv1(argv[1], &cub->map);
}

void	check_argc(int argc, t_map *map)
{
	if (argc < 2)
	{
		printf("Error: missing map file\n");
		bye_game(map);
	}
	else if (argc > 2)
	{
		printf("Error: too many arguments\n");
		bye_game(map);
	}
}

void	check_dotcub(char *argv, t_map *map)
{
	const char	*extension = "./maps/.cub";
	const char	*extension2 = ".cub";

	if (ft_strlen(argv) <= ft_strlen(extension))
	{
		ft_printf("Error: invalid map format\n");
		bye_game(map);
	}
	if (strcmp(argv + ft_strlen(argv)
			- ft_strlen(extension2), extension2) != 0)
	{
		ft_printf("Error: file does not end with '.cub'\n");
		bye_game(map);
	}
}

void	process_argv1(char *argv, t_map *map)
{
	char	*temp;
	int		fd;

	temp = NULL;
	fd = open_file(argv, map);
	temp = check_header(map, temp, &fd);
	missing_info(map);
	close(fd);
	if (temp)
		free(temp);
	check_map(map, argv);
	close(fd);
}

int	open_file(char *argv, t_map *map)
{
	int	file_descriptor;

	file_descriptor = open (argv, O_RDONLY);
	if (file_descriptor < 0)
	{
		ft_printf("Error: can not open file\n");
		bye_game(map);
	}
	return (file_descriptor);
}
