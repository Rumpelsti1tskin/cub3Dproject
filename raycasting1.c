/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:11:35 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:11:35 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rotate_right(t_cub *cub)
{
	double	temp_dir_x;
	double	temp_plane_x;

	temp_dir_x = cub->player->dir_x;
	temp_plane_x = cub->player->plane_x;
	cub->player->dir_x = cub->player->dir_x
		* cos(-cub->player->rot_speed) - cub->player->dir_y
		* sin(-cub->player->rot_speed);
	cub->player->dir_y = temp_dir_x
		* sin(-cub->player->rot_speed) + cub->player->dir_y
		* cos(-cub->player->rot_speed);
	cub->player->plane_x = cub->player->plane_x
		* cos(-cub->player->rot_speed) - cub->player->plane_y
		* sin(-cub->player->rot_speed);
	cub->player->plane_y = temp_plane_x
		* sin(-cub->player->rot_speed) + cub->player->plane_y
		* cos(-cub->player->rot_speed);
}

int	cub_keys(t_keyword key, t_cub *cub)
{
	if (key == ESC)
		exit_cub(cub);
	if (key == W || key == UP_ARR)
		move_up_down(cub->map, cub->player, 'w');
	if (key == S || key == DOWN_ARR)
		move_up_down(cub->map, cub->player, 's');
	if (key == A)
		move_left_right(cub->map, cub->player, 'a');
	if (key == D)
		move_left_right(cub->map, cub->player, 'd');
	if (key == LEFT_ARR)
		rotate_left(cub);
	if (key == RIGHT_SRR)
		rotate_right(cub);
	rays(cub);
	return (0);
}

void	rays(t_cub *cub)
{
	cub->img = malloc(sizeof(t_texture));
	if (!cub->img)
		free_and_exit(cub, "Error\nMalloc error\n");
	cub->img->addr = NULL;
	cub->img->bpp = 0;
	cub->img->endian = 0;
	cub->img->line_len = 0;
	cub->img->img = NULL;
	cub->img->height = 0;
	cub->img->width = 0;
	cub->img->line_height = 0;
	cub->img->draw_end = 0;
	cub->img->draw_start = 0;
	cub->img->img = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bpp,
			&cub->img->line_len, &cub->img->endian);
	get_color(cub);
	start_rays(cub);
	mlx_clear_window(cub->mlx, cub->mlx_win);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img->img);
	cub->img->img = NULL;
	free(cub->img);
}

void	raycasting(t_cub *cub)
{
	int	px;
	int	py;

	px = (int)cub->player->player_x;
	py = (int)cub->player->player_y;
	cub->map->map[py][px] = '0';
	cub->mlx = mlx_init();
	if (!cub->mlx)
		free_and_exit(cub, "Error\nMLX init error\n");
	generate_textures(cub);
	cub->mlx_win = mlx_new_window(cub->mlx,
			SCREEN_WIDTH, SCREEN_HIGHT, "Cub3D");
	rays(cub);
	mlx_hook(cub->mlx_win, 17, 0, exit_cub, cub);
	mlx_hook(cub->mlx_win, 2, 1L << 0, cub_keys, cub);
	mlx_loop(cub->mlx);
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	mlx_destroy_display(cub->mlx);
}
