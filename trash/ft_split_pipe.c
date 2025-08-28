/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:45:54 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/12 16:09:53 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

static char	*mkword(const char *s, char c);
static int	cw(const char *s, char c);
// static char	**freesplit(char **tab);

char	**ft_split_pipe(char const *s, char c)
{
	char	*s1;
	char	**ret;
	char	**ret0;

	if (!cw(s, c))
		return (ft_putstr_fd("minishell: parse error near `|'\n", 2), NULL);
	ret = malloc(sizeof(char *) * (cw(s, c) + 1));
	if (!ret)
		return (ft_putstr_fd("malloc failure\n", 2), NULL);
	ret0 = ret;
	s1 = (char *)s;
	while (*s1)
	{
		if ((s == s1) || (*(s1 - 1) == c) || (!*(s1 + 1) && *s1 == c))
		{
			*ret = mkword(s1, c);
			if (*ret++ == 0)
				return (ft_putstr_fd("malloc failure\n", 2), freesplit(ret0));
		}
		if (*(s1 + 1) && s1 != s && *(s1 - 1) == c)
			s1++;
		s1++;
	}
	*ret = 0;
	return (ret0);
}

static char	*mkword(const char *s, char c)
{
	char	*s1;
	char	*p0;
	char	*p;
	int		l;

	l = 1;
	s1 = (char *)s;
	if (*s1 && *s1 == c)
		l++;
	while (*s1 && *s1 != c)
		s1++;
	p = malloc(sizeof(char) * (s1 - s + l));
	p0 = p;
	if (!p)
		return (0);
	s1 = (char *)s;
	if (*s1 && *s1 == c)
		*p++ = *s1;
	while (*s1 && *s1 != c)
		*p++ = *s1++;
	*p = 0;
	return (p0);
}

static int	cw(const char *s, char c)
{
	char	*s1;
	int		nw;

	nw = 0;
	s1 = (char *)s;
	while (*s1)
	{
		if ((s == s1) || (*(s1 - 1) == c) || (!*(s1 + 1) && *s1 == c))
		{
			if (*s1 == c)
				return (0);
			nw++;
		}
		if (*(s1 + 1) && s1 != s && *(s1 - 1) == c)
			s1++;
		s1++;
	}
	return (nw);
}

// #include <stdio.h>
// #include <string.h>
// int	main(int argc, char **argv)
// {
// 	int i;
// 	char **pr;
//
// 	i = 0;
// 	if (argc != 4)
// 		return (1);
// 	pr = ft_split(argv[1], *argv[2]);
// 	while (i < ft_atoi(argv[3]))
// 		printf("ML: %s\n", pr[i++]);
// 	return (1);
// }