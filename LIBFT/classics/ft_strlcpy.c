/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:53:09 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/04 14:24:16 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	ret;

	ret = ft_strlen(src);
	if (siz == 0)
		return (ret);
	while (*src && siz-- - 1)
		*dst++ = *src++;
	*dst = 0;
	return (ret);
}

// #include <stdio.h>
// #include <bsd/string.h>
// int main (int argc, char **argv)
// {
// 	char dst[10];
// 	size_t size;

// 	size = 5;
// 	if (argc > 0)
// 		argv++;
// 	printf("OG: %ld\nML:%ld\n", strlcpy(dst, *argv, size),
// ft_strlcpy(dst, *argv, size));
// 	return (0);
// }
