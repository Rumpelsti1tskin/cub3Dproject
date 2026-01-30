/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_funcs1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:08:52 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:08:52 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*ptr;
	int		start;
	int		end;

	start = 0;
	end = 0;
	if (!s1)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (nolength(s1));
	while (ft_strchr(set, s1[start]) && s1[start] != '\0')
		start++;
	while (ft_strchr(set, s1[ft_strlen(s1) - end - 1])
		&& (ft_strlen(s1) - end - 1) > start)
		end++;
	ptr = (char *)malloc((ft_strlen(s1) - start - end + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1 + start, ft_strlen(s1) - start - end + 1);
	return (ptr);
}

int	ft_count(char *str, char letter)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == letter)
			i++;
		if (str[i] != letter && str[i] != '\0')
			count++;
		while (str[i] != letter && str[i] != '\0')
			i++;
	}
	return (count);
}

char	*ft_fill_words(char *s, char c)
{
	int		len;
	char	*word;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len > 0)
	{
		word[len - 1] = s[len - 1];
		len--;
	}
	return (word);
}

char	**ft_split(char *s, char c)
{
	char	**ptr;
	size_t	j;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_count(s, c);
	j = 0;
	ptr = (char **)malloc((size + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s)
			ptr[j] = ft_fill_words(s, c);
		while (*s != c && *s != '\0')
			s++;
		j++;
	}
	ptr[size] = NULL;
	return (ptr);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	l;

	i = 0;
	l = 0;
	n = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (0);
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		l = (l * 10) + (str[i] - 48);
		i++;
	}
	return (l * n);
}
