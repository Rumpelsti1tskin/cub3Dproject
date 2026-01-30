/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:12:00 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:12:00 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_white(char element)
{
	if (element == ' ' || element == '\t' || element == '\v'
		|| element == '\f' || element == '\r')
		return (0);
	return (1);
}

int	is_empty_str(char *str)
{
	int	iter;

	if (!str)
		return (0);
	iter = 0;
	while (str[iter] && !is_white(str[iter]))
		++iter;
	if (str[iter] == '\n' || str[iter] == '\0')
		return (0);
	return (1);
}

int	is_valid_symbol(char c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	is_dir(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

void	trim_the_nl(t_cub *cub)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < cub->map->map_h)
	{
		temp = cub->map->map[i];
		cub->map->map[i] = ft_strtrim(temp, "\n");
		free(temp);
		temp = NULL;
		++i;
	}
	return ;
}
