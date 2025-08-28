/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:52:08 by mlagniez          #+#    #+#             */
/*   Updated: 2025/06/14 18:08:04 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	is_end(char *check)
{
	while (*check)
	{
		if (*check++ == '\n')
			return (1);
	}
	return (0);
}

size_t	ft_strlcat_gnl(char *dst, const char src[], size_t siz)
{
	unsigned int	i;
	unsigned int	sd;
	unsigned int	ss;

	sd = ft_strlen_x(dst, 0);
	ss = ft_strlen_x(src, 0);
	if (siz < 1)
		return (ss);
	i = 0;
	while (src[i] && (i + sd < siz - 1))
	{
		dst[i + sd] = src[i];
		i++;
	}
	dst[i + sd] = '\0';
	if (siz < sd)
		return (siz + ss);
	return (sd + ss);
}

size_t	ft_strlen_x(const char *s, int bn)
{
	int	c;

	c = 0;
	while (s && s[c])
	{
		c += 1;
		if (s[c - 1] == '\n' && bn)
			break ;
	}
	return (c);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t siz)
{
	size_t	ret;
	int		i;

	i = -1;
	ret = ft_strlen_x(src, 0);
	if (siz == 0)
		return (ret);
	while (src && dst && src[++i] && siz-- - 1)
		dst[i] = src[i];
	dst[i] = 0;
	return (ret);
}

char	*freetail(char *tail)
{
	if (tail)
		free(tail);
	return (NULL);
}
