#include "../include/cub.h"

void    frame_speed(t_game *cub)
{
    static mlx_image_t  *image;
    char                *fps_text;
	char				*fps_nbr;

    cub->frame_time = 1.0 /cub->mlx->delta_time;
	if (image)
		mlx_delete_image(cub->mlx, image);
	fps_nbr = ft_itoa((int)cub->frame_time);
	fps_text = ft_strjoin("FPS:", fps_nbr);
	free(fps_nbr);
	image = mlx_put_string(cub->mlx, fps_text, WIDTH - 80, HEIGHT - 790);
	free(fps_text);
}


void    key_data(mlx_key_data_t pressed, void *param)
{
    t_game  *cub;

    cub = (t_game *)param;
    if (pressed.key == MLX_KEY_ESCAPE && pressed.action == MLX_PRESS)
    {
        bye_bye(cub);
		mlx_close_window(cub->mlx);
        return ;
    }
    if (pressed.action == MLX_PRESS || pressed.action == MLX_REPEAT)
	// if (pressed.action == MLX_PRESS)
    {
        if (pressed.key == MLX_KEY_W)
            cub->key.w = true;
		if (pressed.key == MLX_KEY_S)
            cub->key.s = true;
		if (pressed.key == MLX_KEY_A)
            cub->key.a = true;
		if (pressed.key == MLX_KEY_D)
            cub->key.d = true;
		if (pressed.key == MLX_KEY_LEFT)
            cub->key.left = true;
		if (pressed.key == MLX_KEY_RIGHT)
            cub->key.right = true;
    }
    else if (pressed.action == MLX_RELEASE)
    {
		if (pressed.key == MLX_KEY_W)
			cub->key.w = false;
		if (pressed.key == MLX_KEY_S)
			cub->key.s = false;
		if (pressed.key == MLX_KEY_A)
			cub->key.a = false;
		if (pressed.key == MLX_KEY_D)
			cub->key.d = false;
		if (pressed.key == MLX_KEY_LEFT)
			cub->key.left = false;
		if (pressed.key == MLX_KEY_RIGHT)
			cub->key.right = false;
	}
}
