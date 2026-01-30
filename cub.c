/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:09:00 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:09:00 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_bzero(void *ptr, size_t n)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = ptr;
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
		exit_error("Error\nWrong number of args");
	cub = malloc(sizeof(t_cub));
	if (!cub)
		exit_error("Error\nMalloc error\n");
	ft_bzero(cub, sizeof(t_cub));
	cub->file_name = NULL;
	cub->map = NULL;
	cub->player = NULL;
	cub->rays = NULL;
	cub->wall = NULL;
	get_info(cub, argc, argv);
	validate(cub);
	raycasting(cub);
	if (cub)
		free_cub(cub);
}
