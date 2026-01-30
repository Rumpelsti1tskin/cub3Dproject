/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:11:31 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:11:31 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_tex(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

void	generate_textures(t_cub *cub)
{
	int	i;

	i = 0;
	checking_gen_tex(cub);
	cub->texture[0]->img = mlx_xpm_file_to_image(cub->mlx,
			cub->map->no, &cub->texture[0]->width, &cub->texture[0]->height);
	cub->texture[1]->img = mlx_xpm_file_to_image(cub->mlx,
			cub->map->so, &cub->texture[1]->width, &cub->texture[1]->height);
	cub->texture[2]->img = mlx_xpm_file_to_image(cub->mlx,
			cub->map->ea, &cub->texture[2]->width, &cub->texture[2]->height);
	cub->texture[3]->img = mlx_xpm_file_to_image(cub->mlx,
			cub->map->we, &cub->texture[3]->width, &cub->texture[3]->height);
	while (i < TEX_NUM)
	{
		cub->texture[i]->addr = mlx_get_data_addr(cub->texture[i]->img,
				&cub->texture[i]->bpp,
				&cub->texture[i]->line_len,
				&cub->texture[i]->endian);
		++i;
	}
}

void	getting_delta_vals(t_cub *cub)
{
	if (cub->rays->ray_dir_x < 0)
	{
		cub->rays->step_x = -1;
		cub->rays->side_dist_x = (cub->player->player_x
				- cub->rays->map_x) * cub->rays->delta_dist_x;
	}
	else
	{
		cub->rays->step_x = 1;
		cub->rays->side_dist_x = (cub->rays->map_x + 1.0
				- cub->player->player_x) * cub->rays->delta_dist_x;
	}
	if (cub->rays->ray_dir_y < 0)
	{
		cub->rays->step_y = -1;
		cub->rays->side_dist_y = (cub->player->player_y
				- cub->rays->map_y) * cub->rays->delta_dist_y;
	}
	else
	{
		cub->rays->step_y = 1;
		cub->rays->side_dist_y = (cub->rays->map_y + 1.0
				- cub->player->player_y) * cub->rays->delta_dist_y;
	}
}

void	perform_dda(t_cub *cub)
{
	while (cub->rays->hit == 0)
	{
		if (cub->rays->side_dist_x < cub->rays->side_dist_y)
		{
			cub->rays->side_dist_x += cub->rays->delta_dist_x;
			cub->rays->map_x += cub->rays->step_x;
			cub->rays->side = 0;
		}
		else
		{
			cub->rays->side_dist_y += cub->rays->delta_dist_y;
			cub->rays->map_y += cub->rays->step_y;
			cub->rays->side = 1;
		}
		if (cub->map->map[cub->rays->map_y][cub->rays->map_x] == '1')
			cub->rays->hit = 1;
	}
	if (cub->rays->side == 0)
		cub->rays->perp_wall_dist = cub->rays->side_dist_x
			- cub->rays->delta_dist_x;
	else
		cub->rays->perp_wall_dist = cub->rays->side_dist_y
			- cub->rays->delta_dist_y;
}

void	calculate_height(t_cub *cub)
{
	cub->wall->line_height = (int)(SCREEN_HIGHT / cub->rays->perp_wall_dist);
	cub->img->draw_start = -cub->wall->line_height / 2 + SCREEN_HIGHT / 2;
	if (cub->img->draw_start < 0)
		cub->img->draw_start = 0;
	cub->img->draw_end = cub->wall->line_height / 2 + SCREEN_HIGHT / 2;
	if (cub->img->draw_end >= SCREEN_HIGHT)
		cub->img->draw_end = SCREEN_HIGHT - 1;
}
