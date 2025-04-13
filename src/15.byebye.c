/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15.byebye.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:50:55 by jbolanho          #+#    #+#             */
/*   Updated: 2025/04/13 18:19:19 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_ptrptr(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

void	close_cub(void *param)
{
	t_game	*cub;

	cub = (t_game *)param;
	bye_bye(cub, EXIT_SUCCESS);
}

void	bye_bye(t_game *cub, int code)
{
	if (cub->no)
		mlx_delete_texture(cub->no);
	if (cub->so)
		mlx_delete_texture(cub->so);
	if (cub->we)
		mlx_delete_texture(cub->we);
	if (cub->ea)
		mlx_delete_texture(cub->ea);
	if (cub->map.north_path)
		free(cub->map.north_path);
	if (cub->map.south_path)
		free(cub->map.south_path);
	if (cub->map.east_path)
		free(cub->map.east_path);
	if (cub->map.west_path)
		free(cub->map.west_path);
	if (cub->map.cub_map)
		free_ptrptr(cub->map.cub_map);
	if (cub->mlx)
		bye_mlx(cub);
	exit(code);
}

void	bye_mlx(t_game *cub)
{
	if (cub->image)
		mlx_delete_image(cub->mlx, cub->image);
	mlx_close_window(cub->mlx);
	mlx_terminate(cub->mlx);
}

void	bye_game(t_map *map)
{
	if (map->north_path)
		free(map->north_path);
	if (map->south_path)
		free(map->south_path);
	if (map->east_path)
		free(map->east_path);
	if (map->west_path)
		free(map->west_path);
	if (map && map->cub_map)
		free_ptrptr(map->cub_map);
}

void	exit_rgb_error(t_map *map, char *temp, const char *msg)
{
	ft_printf("%s :%s\n", msg, temp);
	free(temp);
	bye_game(map);
	exit(EXIT_FAILURE);
}
