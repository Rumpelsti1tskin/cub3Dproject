/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:09:42 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:09:42 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	define_dir(t_cub *cub, int row, int col)
{
	cub->player->player_x = col + 0.5;
	cub->player->player_y = row + 0.5;
	if (cub->map->map[row][col] == 'N')
	{
		cub->player->dir_x = 0;
		cub->player->dir_y = -1;
	}
	else if (cub->map->map[row][col] == 'S')
	{
		cub->player->dir_x = 0;
		cub->player->dir_y = 1;
	}
	else if (cub->map->map[row][col] == 'W')
	{
		cub->player->dir_x = -1;
		cub->player->dir_y = 0;
	}
	else if (cub->map->map[row][col] == 'E')
	{
		cub->player->dir_x = 1;
		cub->player->dir_y = 0;
	}
	init_plane(cub);
}

void	add_line(t_cub *cub, int hight, int i)
{
	char	**new_map;

	new_map = (char **)malloc((hight + 2) * sizeof(char *));
	if (!new_map)
		free_and_exit(cub, "Error\nMalloc error\n");
	while (i < hight)
	{
		new_map[i] = ft_strdup(cub->map->map[i]);
		if (!new_map[i])
		{
			while (--i >= 0)
				free(new_map[i]);
			free(new_map);
			free_and_exit(cub, "Error\nMalloc error\n");
		}
		++i;
	}
	new_map[hight] = ft_strdup(cub->map->info);
	new_map[hight + 1] = NULL;
	free_arr(cub->map->map);
	cub->map->map = new_map;
}

void	add_line_to_map(t_cub *cub)
{
	int		hight;
	int		i;

	hight = 0;
	i = 0;
	while (cub->map->map && cub->map->map[hight])
		++hight;
	add_line(cub, hight, i);
	++cub->map->map_h;
	return ;
}
