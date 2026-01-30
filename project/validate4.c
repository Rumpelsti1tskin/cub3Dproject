/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:32:14 by ykisibek          #+#    #+#             */
/*   Updated: 2025/06/01 14:32:14 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_texture_path(t_cub *cub, char *temp, t_path p)
{
	if (p == NO)
	{
		free(cub->map->no);
		cub->map->no = temp;
	}
	else if (p == SO)
	{
		free(cub->map->so);
		cub->map->so = temp;
	}
	else if (p == EA)
	{
		free(cub->map->ea);
		cub->map->ea = temp;
	}
	else if (p == WE)
	{
		free(cub->map->we);
		cub->map->we = temp;
	}
}

void	validate_paths_1(t_cub *cub, char *path, t_path p)
{
	int		len;
	char	*temp;

	temp = ft_strtrim(path, "\n \t\v\f\r");
	len = ft_strlen(temp);
	if (len < 4 || temp[len - 1] != 'm' || temp[len - 2] != 'p'
		|| temp[len - 3] != 'x' || temp[len - 4] != '.')
	{
		if (temp)
		{
			free(temp);
			temp = NULL;
		}
		free_and_exit(cub, "Error\nWrong texture path");
	}
	set_texture_path(cub, temp, p);
}

int	count_parts(char **temp)
{
	int	count;

	count = 0;
	while (temp[count])
	{
		if (!ft_strncmp(temp[count], "", 1)
			|| !(ft_strncmp(temp[count], "\n", 1)))
			break ;
		++count;
	}
	return (count);
}

static void	rgb_col(t_cub *cub, char **temp, char c)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_arr(temp);
		temp = NULL;
		free_and_exit(cub, "Error\nWrong color\n");
	}
	if (c == 'c')
		cub->map->col_c = (r << 16) | (g << 8) | b;
	else if (c == 'f')
		cub->map->col_f = (r << 16) | (g << 8) | b;
}

void	validate_color(t_cub *cub, char *col, char c)
{
	char	**temp;
	int		count;

	count = 0;
	temp = ft_split(col, ',');
	if (!temp)
		free_and_exit(cub, "Error\nMalloc error\n");
	count = count_parts(temp);
	if (count != 3)
	{
		free_arr(temp);
		free_and_exit(cub, "Error\nWrong color\n");
	}
	rgb_col(cub, temp, c);
	free_arr(temp);
	return ;
}
