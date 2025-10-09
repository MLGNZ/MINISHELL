/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:27:34 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 14:43:39 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cat_over_quotes(const char *s0, char *s, char q);

void	remove_quotes(const char *s0, char *s)
{
	char	q;

	while (s && *s)
	{
		if (is_meta(s, '\'', (char *)s0))
			q = '\'';
		else if (is_meta(s, '\"', (char *)s0))
			q = '\"';
		else
			q = 0;
		if (q)
			s += cat_over_quotes(s, s, q);
		else
			s++;
	}
}

static int	cat_over_quotes(const char *s0, char *s, char q)
{
	int	len;

	len = 0;
	ft_strlcpy(s, s + 1, ft_strlen(s));
	while (*s)
	{	
		if (is_meta(s, q, (char *)s0))
		{
			len = (s - s0);
			break ;
		}
		s++;
	}
	ft_strlcpy(s, s + 1, ft_strlen(s));
	return (len);
}

void	remove_backslashes(const char *s0, char *s)
{
	while (s0 && *s)
	{
		if (*s == '\\')
			ft_strlcpy(s, s + 1, ft_strlen(s + 1) + 1);
		s++;
	}
}

int	how_many_backslashes(char *s0, char *s)
{
	int	n;

	n = 0;
	while (s > s0)
	{
		s--;
		if (*s == '\\')
			n++;
		else
			break ;
	}
	return (n);
}
