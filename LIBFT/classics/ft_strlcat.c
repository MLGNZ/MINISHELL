/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:37:02 by mlagniez          #+#    #+#             */
/*   Updated: 2025/06/14 18:09:55 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	unsigned int	i;
	unsigned int	sd;
	unsigned int	ss;

	sd = ft_strlen(dst);
	ss = ft_strlen(src);
	if (siz < 1)
		return (ss);
	i = 0;
	while (src && src[i] && (i + sd < siz - 1))
	{
		dst[i + sd] = src[i];
		i++;
	}
	dst[i + sd] = '\0';
	if (siz < sd)
		return (siz + ss);
	return (sd + ss);
}

// #include <stdio.h>
// #include <bsd/string.h>

// int	main(void)
// {
// 	char			dest1[50] = "hello to the";
// 	char			dest2[50] = "hello to the";
// 	char			src[] = "worl";
// 	unsigned int	size = 20;
// 	int				lib;
// 	int				mine;

// 	lib = ft_strlcat(dest1, src, size);
// 	mine = ft_strlcat(dest2, src, size);
// 	printf("Size: %i\n", size);
// 	printf("strlcat:\nReturn (fyi):%i\nDest:%s\n\n", lib, dest1);
// 	printf("ft_strlcat:\nReturn (fyi):%i\n", mine);
// 	printf("Dest:%s", dest2);
// }
