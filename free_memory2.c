/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:13:59 by ykisibek          #+#    #+#             */
/*   Updated: 2025/06/01 17:24:08 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_texture(t_texture **texture)
{
	int	i;

	i = 0;
	while (i < TEX_NUM)
	{
		if (texture[i])
		{
			free(texture[i]);
			texture[i] = NULL;
		}
		++i;
	}
	free(texture);
	texture = NULL;
}
