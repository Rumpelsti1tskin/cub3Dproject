/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:11:57 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:11:57 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_colors(t_cub *cub, char *info, t_path path)
{
	if (path == C)
	{
		if (cub->map->c_col)
			free_and_exit(cub, "Error\nWrong directions\n");
		cub->map->c_col = ft_strtrim(info, WHITE_SPACE);
		if (!cub->map->c_col)
			free_and_exit(cub, "Error\nMalloc error\n");
	}
	else if (path == F)
	{
		if (cub->map->f_col)
			free_and_exit(cub, "Error\nWrong directions\n");
		cub->map->f_col = ft_strtrim(info, WHITE_SPACE);
		if (!cub->map->f_col)
			free_and_exit(cub, "Error\nMalloc error\n");
	}
	return (1);
}

int	get_path1(t_cub *cub, char *info, t_path path)
{
	if (path == WE)
	{
		if (cub->map->we)
			free_and_exit(cub, "Error\nWrong directions\n");
		cub->map->we = ft_strtrim(info, WHITE_SPACE);
		if (!cub->map->we)
			free_and_exit(cub, "Error\nMalloc error\n");
	}
	else if (path == EA)
	{
		if (cub->map->ea)
			free_and_exit(cub, "Error\nWrong directions\n");
		cub->map->ea = ft_strtrim(info, WHITE_SPACE);
		if (!cub->map->ea)
			free_and_exit(cub, "Error\nMalloc error\n");
	}
	else if (path == F || path == C)
		get_colors(cub, info, path);
	return (1);
}

int	get_path(t_cub *cub, char *info, t_path path)
{
	if (path == NO)
	{
		if (cub->map->no)
			free_and_exit(cub, "Error\nWrong directions\n");
		cub->map->no = ft_strtrim(info, WHITE_SPACE);
		if (!cub->map->no)
			free_and_exit(cub, "Error\nMalloc error\n");
	}
	else if (path == SO)
	{
		if (cub->map->so)
			free_and_exit(cub, "Error\nWrong directions\n");
		cub->map->so = ft_strtrim(info, WHITE_SPACE);
		if (!cub->map->so)
			free_and_exit(cub, "Error\nMalloc error\n");
	}
	else if (path == WE || path == EA || path == C || path == F)
		get_path1(cub, info, path);
	else
		return (0);
	return (1);
}

int	get_path_info(t_cub *cub, char *info)
{
	int		white_len;

	white_len = 0;
	if (!info)
		return (0);
	while (info[white_len] && !is_white(info[white_len]))
		++white_len;
	info += white_len;
	if (info[0] == '\n')
		return (1);
	else if (!ft_strncmp(info, "NO", 2))
		return (get_path(cub, info + 2, NO));
	else if (!ft_strncmp(info, "SO", 2))
		return (get_path(cub, info + 2, SO));
	else if (!ft_strncmp(info, "WE", 2))
		return (get_path(cub, info + 2, WE));
	else if (!ft_strncmp(info, "EA", 2))
		return (get_path(cub, info + 2, EA));
	else if (!ft_strncmp(info, "C", 1))
		return (get_path(cub, info + 1, C));
	else if (!ft_strncmp(info, "F", 1))
		return (get_path(cub, info + 1, F));
	return (0);
}
