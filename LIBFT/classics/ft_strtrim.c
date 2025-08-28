/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:25:38 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/07 16:19:11 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char *set);
static int	isnottheending(char *s, char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ss;
	char	*se;

	ss = (char *)s1;
	while (*ss && is_set(*ss, (char *)set))
		ss++;
	se = ss;
	while (*se && isnottheending(se, (char *)set))
		se++;
	return (ft_substr(s1, ss - s1, se - ss));
}

static int	is_set(char c, char *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

static int	isnottheending(char *s, char *set)
{
	while (*s)
	{
		if (!is_set(*s++, set))
			return (1);
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 3)
// 		return (1);
// //	printf("OG: %s\n", substr(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3])));
// 	printf("ML: %s\n", ft_strtrim(argv[1], argv[2]));
// 	return (1);
// }