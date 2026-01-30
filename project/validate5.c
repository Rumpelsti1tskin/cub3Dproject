/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:31:33 by ykisibek          #+#    #+#             */
/*   Updated: 2025/06/01 14:31:33 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_map_row(t_cub *cub, int row, int *p_dir_count)
{
	int	col;

	col = 0;
	while (cub->map->map[row][col])
	{
		if (!is_valid_symbol(cub->map->map[row][col]))
			free_and_exit(cub, "Error\nNot valid symbol used\n");
		if (is_dir(cub->map->map[row][col]))
		{
			(*p_dir_count)++;
			define_dir(cub, row, col);
		}
		col++;
	}
	if (!is_empty_str(cub->map->map[row]))
		free_and_exit(cub, "Error\nEmpty line in your map\n");
}

void	check_for_symbols(t_cub *cub)
{
	int	p_dir_count;
	int	row;

	p_dir_count = 0;
	row = 0;
	while (row < cub->map->map_h)
	{
		check_map_row(cub, row, &p_dir_count);
		row++;
	}
	if (p_dir_count != 1)
		free_and_exit(cub, "Error\nWrong amount of directions\n");
}

void	check_name(t_cub *cub)
{
	int		point;

	point = ft_strlen(cub->file_name);
	if (point < 4 || cub->file_name[point] != '\0'
		|| cub->file_name[point - 1] != 'b'
		|| cub->file_name[point - 2] != 'u' || cub->file_name[point - 3] != 'c'
		|| cub->file_name[point - 4] != '.')
		free_and_exit(cub, "Error\nWrong file name\n");
}
