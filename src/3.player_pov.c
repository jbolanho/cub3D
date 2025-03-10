#include "../include/cub.h"

void    frame_speed(t_game *cub)
{
    static mlx_image_t  *image;
    char                *fps_text;

    cub->frame_time = 1.0 /cub->mlx->delta_time;
    if (image)
        mlx_delete_image(cub->mlx, image);
    fps_text = ft_strjoin("FPS:", ft_itoa((int)cub->frame_time));
    image = mlx_put_string(cub->mlx, fps_text, WIDTH - 80, HEIGHT - 790);
    // free(fps_text);
}
