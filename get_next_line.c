/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:17:12 by ykisibek          #+#    #+#             */
/*   Updated: 2024/03/03 16:17:13 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*fill_line(char *line, int fd)
{
	char	*line_read;
	int		chars_read;

	line_read = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line_read)
		return (NULL);
	chars_read = 1;
	while (!(ft_strchr(line, '\n')) && chars_read != 0)
	{
		chars_read = read(fd, line_read, BUFFER_SIZE);
		if (chars_read < 0)
		{
			free(line_read);
			free(line);
			line = NULL;
			return (NULL);
		}
		line_read[chars_read] = '\0';
		line = ft_strjoin(line, line_read);
	}
	free(line_read);
	line_read = NULL;
	return (line);
}

int	count_nl(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

char	*free_from_nl(char *line)
{
	int		size;
	char	*left_line;
	int		i;
	int		j;

	if (!line || !(*line))
		return (NULL);
	i = count_nl(line);
	j = gnl_strlen(line);
	size = j - i + 1;
	left_line = (char *)malloc(size * sizeof(char));
	if (!left_line)
		return (NULL);
	size--;
	while (size >= 0)
		left_line[size--] = line[j--];
	free(line);
	line = NULL;
	return (left_line);
}

char	*copy_with_nl(char *line)
{
	int		i;
	char	*send;

	if (!line || !(*line))
		return (NULL);
	send = (char *)malloc((count_nl(line) + 1) * sizeof(char));
	if (!send)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		send[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		send[i] = '\n';
		send[i + 1] = '\0';
	}
	else
		send[i] = '\0';
	return (send);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*line_to_send;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = fill_line(line, fd);
	if (!line)
		return (NULL);
	line_to_send = copy_with_nl(line);
	if (!line_to_send)
	{
		free (line);
		line = NULL;
		return (NULL);
	}
	line = free_from_nl(line);
	return (line_to_send);
}
