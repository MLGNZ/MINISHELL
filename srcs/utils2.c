/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 03:24:05 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/13 18:07:39 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printsplit(char **split)
{
	if (!split)
		printf("none\n");
	while (split && *split)
	{
		puts(*split);
		split++;
	}
}

char	is_meta(char *c_address, char meta, char *s0)
{
	if (*c_address == meta && (s0 == c_address \
		|| !(how_many_backslashes(s0, c_address) % 2)))
		return (meta);
	return (0);
}

char	meta_char(char *rline, char *rline0)
{
	if (is_meta(rline, '|', rline0))
		return ('|');
	else if (is_meta(rline, '\'', rline0))
		return ('\'');
	else if (is_meta(rline, '\"', rline0))
		return ('\"');
	return (0);
}

int	is_int(char *s)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	while (s[++i] && ft_isdigit(s[i]))
		len++;
	if (len < 10)
		return (len);
	else if (ft_strncmp(s, "2147483647", len) <= 0)
		return (len);
	return (0);
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
