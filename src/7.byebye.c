#include "../include/cub.h"

// void	free_texture(t_game *cub)
// {
// 	if (cub->no)
// 		mlx_delete_texture(cub->no);
// 	if (cub->so)
// 		mlx_delete_texture(cub->so);
// 	if (cub->we)
// 		mlx_delete_texture(cub->we);
// 	if (cub->ea)
// 		mlx_delete_texture(cub->ea);
// 	if(cub)
// 		free_map(&cub->map);	
// }

// void	free_map(t_map	*map)
// {
// 	if(map->north_path)
// 		free(map->north_path);
// 	if(map->south_path)
// 		free(map->south_path);
// 	if(map->east_path)
// 		free(map->east_path);
// 	if(map->west_path)
// 		free(map->west_path);
// 	if(map->cub_map)
// 		free_ptrptr(map->cub_map);
// 	if(map)
// 		free(map);
// }

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
	bye_bye(cub);
	mlx_close_window(cub->mlx);
}

void	bye_bye(t_game *cub)
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
	if(cub->map.south_path)
		free(cub->map.south_path);
	if(cub->map.east_path)
		free(cub->map.east_path);
	if(cub->map.west_path)
		free(cub->map.west_path);
	if(cub->map.cub_map)	
        free_ptrptr(cub->map.cub_map);
}
