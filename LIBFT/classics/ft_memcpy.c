/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:51:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:14:54 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (n-- > 0 && (dest || src))
		*d++ = *s++;
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char s[] = "";
// 	char d[] = "";
// 	int	ld;
// 	int	n;
// 	int	i;

// 	i = -1;
// 	n = 5;
// 	ld = ft_strlen(d);
// 	memcpy(d, s, n);
// 	while (++i < ld)
// 		printf("%c\n", d[i]);
// 	return (1);
// }
