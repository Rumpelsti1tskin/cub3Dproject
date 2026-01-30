/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:11:43 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:11:43 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_img_info(t_cub *cub, int x)
{
	double			step;
	double			tex_pos;
	int				y;
	unsigned int	color;
	unsigned int	*tex_pixels;

	step = 1.0 * cub->texture[cub->wall->tex_num]->height
		/ cub->wall->line_height;
	tex_pos = (cub->img->draw_start - SCREEN_HIGHT
			/ 2 + cub->wall->line_height / 2) * step;
	y = cub->img->draw_start;
	while (y < cub->img->draw_end)
	{
		cub->wall->tex_y = (int)tex_pos
			& (cub->texture[cub->wall->tex_num]->height - 1);
		tex_pos += step;
		tex_pixels = (unsigned int *)cub->texture[cub->wall->tex_num]->addr;
		color = tex_pixels[cub->wall->tex_y
			* cub->texture[cub->wall->tex_num]->width + cub->wall->tex_x];
		if (cub->rays->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		*(unsigned int *)(cub->img->addr
				+ (y * cub->img->line_len + x * (cub->img->bpp / 8))) = color;
		++y;
	}
}

void	init_ray_values(t_cub *cub, int x)
{
	cub->rays->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	cub->rays->ray_dir_x = cub->player->dir_x
		+ cub->player->plane_x * cub->rays->camera_x;
	cub->rays->ray_dir_y = cub->player->dir_y
		+ cub->player->plane_y * cub->rays->camera_x;
	cub->rays->map_x = (int)cub->player->player_x;
	cub->rays->map_y = (int)cub->player->player_y;
	cub->rays->hit = 0;
}

void	calc_ray_distances(t_cub *cub)
{
	if (cub->rays->ray_dir_x == 0)
		cub->rays->delta_dist_x = 1e30;
	else
		cub->rays->delta_dist_x = fabs(1.0 / cub->rays->ray_dir_x);
	if (cub->rays->ray_dir_y == 0)
		cub->rays->delta_dist_y = 1e30;
	else
		cub->rays->delta_dist_y = fabs(1.0 / cub->rays->ray_dir_y);
}

void	start_rays(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray_values(cub, x);
		calc_ray_distances(cub);
		getting_delta_vals(cub);
		perform_dda(cub);
		calculate_height(cub);
		get_tex_x(cub);
		get_img_info(cub, x);
		++x;
	}
}

void	checking_gen_tex(t_cub *cub)
{
	if (check_tex(cub->map->no) || check_tex(cub->map->so)
		|| check_tex(cub->map->ea) || check_tex(cub->map->we))
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		cub->mlx = NULL;
		free_and_exit(cub, "Error\nWrong paths");
	}
}
