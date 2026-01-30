/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:11:47 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:11:47 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_the_map(t_cub *cub)
{
	trim_the_nl(cub);
	check_for_symbols(cub);
	check_up_down_borders(cub);
	check_side_borders(cub);
	check_space_borders(cub);
	return ;
}

void	trim_trailing_empty_lines(t_cub *cub)
{
	int	last_valid;

	last_valid = cub->map->map_h - 1;
	while (last_valid >= 0 && !is_empty_str(cub->map->map[last_valid]))
	{
		free(cub->map->map[last_valid]);
		cub->map->map[last_valid] = NULL;
		last_valid--;
	}
	cub->map->map_h = last_valid + 1;
}

void	get_map_data(t_cub *cub)
{
	cub->map->map_h = 0;
	cub->map->map = NULL;
	add_line_to_map(cub);
	free(cub->map->info);
	while (cub->map->info)
	{
		(cub->map->info) = get_next_line(cub->map->fd);
		add_line_to_map(cub);
		free(cub->map->info);
	}
	cub->map->info = NULL;
	trim_trailing_empty_lines(cub);
	check_the_map(cub);
}

void	validate_paths(t_cub *cub)
{
	if (!cub->map->no || !cub->map->so || !cub->map->we
		|| !cub->map->ea || !cub->map->c_col || !cub->map->f_col)
		free_and_exit(cub, "Error\nWrong directions\n");
	validate_paths_1(cub, cub->map->no, NO);
	validate_paths_1(cub, cub->map->so, SO);
	validate_paths_1(cub, cub->map->ea, EA);
	validate_paths_1(cub, cub->map->we, WE);
	validate_color(cub, cub->map->c_col, 'c');
	validate_color(cub, cub->map->f_col, 'f');
}

void	validate(t_cub *cub)
{
	cub->map->info = get_next_line(cub->map->fd);
	if (!cub->map->info)
		free_and_exit(cub, "Error\nNo info in your file\n");
	while (get_path_info(cub, cub->map->info))
	{
		free(cub->map->info);
		cub->map->info = get_next_line(cub->map->fd);
	}
	validate_paths(cub);
	get_map_data(cub);
}
