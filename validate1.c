/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:11:52 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:11:52 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_up_down_borders(t_cub *cub)
{
	int	row;
	int	col;

	row = 0;
	while (row < cub->map->map_h)
	{
		col = 0;
		if (row == 0 || row == cub->map->map_h - 1)
		{
			while (cub->map->map[row][col])
			{
				if (cub->map->map[row][col] != '1'
					&& cub->map->map[row][col] != ' ')
					free_and_exit(cub, "Error\nWrong borders\n");
				++col;
			}
		}
		++row;
	}
	return ;
}

void	check_the_end(t_cub *cub, int row, int col)
{
	if (row > 0 && (ft_strlen(cub->map->map[row])
			> ft_strlen(cub->map->map[row - 1])
			&& col > ft_strlen(cub->map->map[row - 1]) - 1))
	{
		if (cub->map->map[row][col] != '1')
			free_and_exit(cub, "Error\nWrong map\n");
	}
	if (row < (cub->map->map_h - 1) && (ft_strlen(cub->map->map[row])
			> ft_strlen(cub->map->map[row + 1])
			&& col > ft_strlen(cub->map->map[row + 1]) - 1))
	{
		if (cub->map->map[row][col] != '1')
			free_and_exit(cub, "Error\nWrong map\n");
	}
}

void	check_side_borders(t_cub *cub)
{
	int		row;
	int		col;

	row = 0;
	while (row < cub->map->map_h)
	{
		col = 0;
		while (cub->map->map[row][col] == ' ')
			++col;
		if (cub->map->map[row][col] != '1')
			free_and_exit(cub, "Error\nWrong borders\n");
		col = ft_strlen(cub->map->map[row]) - 1;
		while (col > 0 && cub->map->map[row][col] == ' ')
			--col;
		if (col == 0 || cub->map->map[row][col] != '1')
			free_and_exit(cub, "Error\nWrong borders\n");
		++row;
	}
	return ;
}

void	check_neighbors(t_cub *cub, int row, int col)
{
	if (row > 0 && (cub->map->map[row - 1][col] != ' '
		&& cub->map->map[row - 1][col] != '1'))
		free_and_exit(cub, "Error\nWrong map\n");
	if (row < (cub->map->map_h - 1) && (cub->map->map[row + 1][col] != ' '
		&& cub->map->map[row + 1][col] != '1'))
		free_and_exit(cub, "Error\nWrong map\n");
	if (col > 0 && (cub->map->map[row][col - 1] != ' '
		&& cub->map->map[row][col - 1] != '1'))
		free_and_exit(cub, "Error\nWrong map\n");
	if (col < ((int)ft_strlen(cub->map->map[row]) - 1)
		&& (cub->map->map[row][col + 1] != ' '
		&& cub->map->map[row][col + 1] != '1'))
		free_and_exit(cub, "Error\nWrong map\n");
	return ;
}

void	check_space_borders(t_cub *cub)
{
	int	row;
	int	col;

	row = 0;
	while (row < cub->map->map_h)
	{
		col = 0;
		while (cub->map->map[row][col])
		{
			check_the_end(cub, row, col);
			if (cub->map->map[row][col] == ' ')
				check_neighbors(cub, row, col);
			++col;
		}
		++row;
	}
}
