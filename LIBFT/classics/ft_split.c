/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:45:54 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/27 16:36:16 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*mkword(const char *s, char c);
static int	cw(const char *s, char c);
// static char	**freesplit(char **tab);

char	**ft_split(char const *s, char c)
{
	char	*s1;
	char	**ret;
	char	**ret0;

	ret = malloc(sizeof(char *) * (cw(s, c) + 1));
	if (!ret)
		return (0);
	ret0 = ret;
	s1 = (char *)s;
	while (*s1)
	{
		if ((*s1 != c && s == s1) || (*s1 != c && *(s1 - 1) == c))
		{
			*ret = mkword(s1, c);
			if (*ret++ == 0)
				return (freesplit(ret0));
		}
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

	s1 = (char *)s;
	while (*s1 && *s1 != c)
		s1++;
	p = malloc(sizeof(char) * (s1 - s + 1));
	p0 = p;
	if (!p)
		return (0);
	s1 = (char *)s;
	while (*s1 && *s1 != c)
		*p++ = *s1++;
	*p = 0;
	return (p0);
}

char	**freesplit(char **tab)
{
	char	**tab0;

	tab0 = tab;
	while (tab && *tab)
	{
		free(*(tab));
		// puts(*tab);
		tab++;
	}
	free(tab0);
	return (0);
}

static int	cw(const char *s, char c)
{
	char	*s1;
	int		nw;

	nw = 0;
	s1 = (char *)s;
	while (*s1)
	{
		if ((*s1 != c && s == s1) || (*s1 != c && *(s1 - 1) == c))
			nw++;
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