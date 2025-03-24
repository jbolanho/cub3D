/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.copymap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:24:55 by jbolanho          #+#    #+#             */
/*   Updated: 2025/03/24 13:45:54 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// void	copy_map(t_game *cub)
// {
// 	int		fd;
// 	int		buff;
// 	char	*temp;
//     char    *file;
//     char    buffer[11];

//     file = "./maps/fake_map2.cub";
// 	fd = open_file(file);
// 	temp = ft_strdup("");
// 	buff = read(fd, buffer, 10);
// 	if (buff == -1)
// 		ft_printf("Error reading file");
// 	while (buff > 0)
// 	{
// 		buffer[buff] = '\0';
// 		temp = ft_strjoin(temp, buffer);
// 		buff = read(fd, buffer, 10);
// 	}
// 	if (buff == -1)
//         ft_printf("The map has an error.\n");
// 	cub->map.cub_map = ft_split(temp, '\n');
// 	close(fd);
// 	free(temp);
// }


// void    init(t_game *cub, int argc, char **argv)
// {
//     (void)cub;
//     (void)argc;
//     (void)argv;
//     cub->map.north_path = NULL;
// 	cub->map.south_path = NULL;
// 	cub->map.east_path = NULL;
// 	cub->map.west_path = NULL;
// 	cub->map.floor_color = 0;
// 	cub->map.ceiling_color = 0;
// 	cub->map.cub_map = NULL;
// }