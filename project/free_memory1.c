/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:09:12 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:09:12 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_map1(t_map *map)
{
	if (map->c_col)
	{
		free(map->c_col);
		map->c_col = NULL;
	}
	if (map->f_col)
	{
		free(map->f_col);
		map->f_col = NULL;
	}
	if (map->info)
	{
		free(map->info);
		map->info = NULL;
	}
	if (map->map)
		free_arr(map->map);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->no)
	{
		free(map->no);
		map->no = NULL;
	}
	if (map->so)
	{
		free(map->so);
		map->so = NULL;
	}
	if (map->we)
	{
		free(map->we);
		map->we = NULL;
	}
	if (map->ea)
	{
		free(map->ea);
		map->ea = NULL;
	}
	free_map1(map);
	free(map);
	map = NULL;
}

void	free_rays(t_ray_info *rays)
{
	if (!rays)
		return ;
	free(rays);
	rays = NULL;
}

void	free_wall(t_wall *wall)
{
	if (!wall)
		return ;
	free(wall);
	wall = NULL;
}

void	free_cub(t_cub *cub)
{
	if (cub->file_name)
	{
		if (cub->map && cub->map->fd)
			close(cub->map->fd);
		free(cub->file_name);
		cub->file_name = NULL;
	}
	if (cub->map)
		free_map(cub->map);
	if (cub->player)
		free_player(cub->player);
	if (cub->rays)
		free_rays(cub->rays);
	if (cub->wall)
		free_wall(cub->wall);
	if (cub->texture)
		free_texture(cub->texture);
	free(cub);
	cub = NULL;
}
