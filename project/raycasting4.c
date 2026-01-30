/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:32:37 by ykisibek          #+#    #+#             */
/*   Updated: 2025/06/01 14:32:37 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_texture_number(t_cub *cub)
{
	if (cub->rays->side == 0)
	{
		if (cub->rays->ray_dir_x > 0)
			cub->wall->tex_num = EA;
		else
			cub->wall->tex_num = WE;
	}
	else
	{
		if (cub->rays->ray_dir_y > 0)
			cub->wall->tex_num = SO;
		else
			cub->wall->tex_num = NO;
	}
}

void	calculate_wall_x(t_cub *cub)
{
	if (cub->rays->side == 0)
		cub->wall->wall_x = cub->player->player_y
			+ cub->rays->perp_wall_dist * cub->rays->ray_dir_y;
	else
		cub->wall->wall_x = cub->player->player_x
			+ cub->rays->perp_wall_dist * cub->rays->ray_dir_x;
	cub->wall->wall_x -= floor(cub->wall->wall_x);
}

void	calculate_tex_x(t_cub *cub)
{
	int	num;

	num = cub->wall->tex_num;
	cub->wall->tex_x = (int)(cub->wall->wall_x
			* (double)cub->texture[num]->width);
	if ((cub->rays->side == 0 && cub->rays->ray_dir_x > 0)
		|| (cub->rays->side == 1 && cub->rays->ray_dir_y < 0))
		cub->wall->tex_x = cub->texture[num]->width - cub->wall->tex_x - 1;
}

void	get_tex_x(t_cub *cub)
{
	set_texture_number(cub);
	calculate_wall_x(cub);
	calculate_tex_x(cub);
}

int	exit_cub(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < TEX_NUM)
	{
		mlx_destroy_image(cub->mlx, cub->texture[i]->img);
		cub->texture[i]->img = NULL;
		free(cub->texture[i]);
		cub->texture[i] = NULL;
		++i;
	}
	free(cub->texture);
	cub->texture = NULL;
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	cub->mlx = NULL;
	free_cub(cub);
	exit (0);
}
