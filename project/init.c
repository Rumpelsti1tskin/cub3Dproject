/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:09:37 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:09:37 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_texture(t_cub *cub)
{
	int	i;

	i = 0;
	cub->texture = (t_texture **) malloc
		(sizeof(t_texture *) * TEX_NUM);
	if (!cub->texture)
		free_and_exit(cub, "Error\nMalloc error\n");
	while (i < TEX_NUM)
	{
		cub->texture[i] = malloc(sizeof(t_texture));
		if (!cub->texture[i])
			free_and_exit(cub, "Error\nMalloc error\n");
		cub->texture[i]->img = NULL;
		cub->texture[i]->addr = NULL;
		cub->texture[i]->bpp = 0;
		cub->texture[i]->endian = 0;
		cub->texture[i]->line_len = 0;
		cub->texture[i]->width = 0;
		cub->texture[i]->height = 0;
		cub->texture[i]->line_height = 0;
		cub->texture[i]->draw_end = 0;
		cub->texture[i]->draw_start = 0;
		++i;
	}
}

void	init_cub_map(t_cub *cub, int fd)
{
	cub->map = malloc(sizeof(t_map));
	if (!cub->map)
		free_and_exit(cub, "Error\nMalloc error\n");
	cub->map->fd = fd;
	cub->map->no = NULL;
	cub->map->so = NULL;
	cub->map->we = NULL;
	cub->map->ea = NULL;
	cub->map->c_col = NULL;
	cub->map->f_col = NULL;
	cub->map->map = NULL;
	cub->map->info = NULL;
}

void	init_cub_rays(t_cub *cub)
{
	cub->rays = malloc(sizeof(t_ray_info));
	if (!cub->rays)
		free_and_exit(cub, "Error\nMalloc error\n");
	cub->rays->time = 0;
	cub->rays->old_time = 0;
	cub->rays->camera_x = 0;
	cub->rays->ray_dir_x = 0;
	cub->rays->ray_dir_y = 0;
	cub->rays->side_dist_x = 0;
	cub->rays->side_dist_y = 0;
	cub->rays->delta_dist_x = 0;
	cub->rays->delta_dist_y = 0;
	cub->rays->perp_wall_dist = 0;
	cub->rays->map_x = 0;
	cub->rays->map_y = 0;
	cub->rays->step_x = 0;
	cub->rays->step_y = 0;
	cub->rays->hit = 0;
	cub->rays->side = 0;
}

void	get_info(t_cub *cub, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		free_and_exit(cub, "Error\nWrong number of args\n");
	cub->file_name = ft_strdup(argv[1]);
	if (!cub->file_name)
		free_and_exit(cub, "Error\nSomething wrong with your file\n");
	check_name(cub);
	fd = open(cub->file_name, O_RDONLY);
	if (fd < 0)
		free_and_exit(cub, "Error\nCanot open the file\n");
	init_cub_map(cub, fd);
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		free_and_exit(cub, "Error\nMalloc error\n");
	init_cub_rays(cub);
	cub->wall = malloc(sizeof(t_wall));
	if (!cub->wall)
		free_and_exit(cub, "Error\nMalloc error\n");
	cub->wall->tex_num = 0;
	cub->wall->tex_x = 0;
	cub->wall->tex_y = 0;
	cub->wall->wall_x = 0;
	init_texture(cub);
}

void	init_plane(t_cub *cub)
{
	cub->player->mov_speed = 0.15;
	cub->player->rot_speed = 0.1;
	cub->player->plane_x = cub->player->dir_y * FOV;
	cub->player->plane_y = cub->player->dir_x * FOV;
}
