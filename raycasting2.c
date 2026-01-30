/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:11:39 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:11:39 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fill(t_cub *cub, int y, int map_col)
{
	int				x;
	char			*col;
	unsigned int	color;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		col = cub->img->addr + (y * cub->img->line_len + x
				* (cub->img->bpp / 8));
		color = map_col;
		*(unsigned int *)col = color;
		++x;
	}
}

void	get_color(t_cub *cub)
{
	int	y;

	y = 0;
	while (y < SCREEN_HIGHT / 2)
	{
		fill(cub, y, cub->map->col_c);
		++y;
	}
	while (y < SCREEN_HIGHT)
	{
		fill(cub, y, cub->map->col_f);
		++y;
	}
}

void	move_up_down(t_map *map, t_player *pl, int c)
{
	if (c == 'w')
	{
		if (map->map[(int)pl->player_y][(int)(pl->player_x
			+ pl->dir_x * pl->mov_speed)] == '0')
		{
			pl->player_x += pl->dir_x * pl->mov_speed;
		}
		if (map->map[(int)(pl->player_y + pl->dir_y
				* pl->mov_speed)][(int)pl->player_x] == '0')
			pl->player_y += pl->dir_y * pl->mov_speed;
	}
	else if (c == 's')
	{
		if (map->map[(int)pl->player_y][(int)(pl->player_x - pl->dir_x
			* pl->mov_speed)] == '0')
			pl->player_x -= pl->dir_x * pl->mov_speed;
		if (map->map[(int)(pl->player_y - pl->dir_y
				* pl->mov_speed)][(int)pl->player_x] == '0')
			pl->player_y -= pl->dir_y * pl->mov_speed;
	}
}

void	move_left_right(t_map *map, t_player *pl, int c)
{
	if (c == 'd')
	{
		if (map->map[(int)pl->player_y][(int)(pl->player_x
			+ pl->dir_y * pl->mov_speed)] == '0')
			pl->player_x += pl->dir_y * pl->mov_speed;
		if (map->map[(int)(pl->player_y - pl->dir_x
				* pl->mov_speed)][(int)pl->player_x] == '0')
			pl->player_y -= pl->dir_x * pl->mov_speed;
	}
	else if (c == 'a')
	{
		if (map->map[(int)pl->player_y][(int)(pl->player_x
			- pl->dir_y * pl->mov_speed)] == '0')
			pl->player_x -= pl->dir_y * pl->mov_speed;
		if (map->map[(int)(pl->player_y + pl->dir_x
				* pl->mov_speed)][(int)pl->player_x] == '0')
			pl->player_y += pl->dir_x * pl->mov_speed;
	}
}

void	rotate_left(t_cub *cub)
{
	double	temp_dir_x;
	double	temp_plane_x;

	temp_dir_x = cub->player->dir_x;
	temp_plane_x = cub->player->plane_x;
	cub->player->dir_x = cub->player->dir_x
		* cos(cub->player->rot_speed) - cub->player->dir_y
		* sin(cub->player->rot_speed);
	cub->player->dir_y = temp_dir_x
		* sin(cub->player->rot_speed) + cub->player->dir_y
		* cos(cub->player->rot_speed);
	cub->player->plane_x = cub->player->plane_x
		* cos(cub->player->rot_speed) - cub->player->plane_y
		* sin(cub->player->rot_speed);
	cub->player->plane_y = temp_plane_x
		* sin(cub->player->rot_speed) + cub->player->plane_y
		* cos(cub->player->rot_speed);
}
