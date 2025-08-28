/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:18:01 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:14:28 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	while (n--)
	{
		if ((unsigned char)c == *s2++)
			return ((void *)--s2);
	}
	return (0);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char s[] = "okay";

// 	printf("%s\n", (char *)ft_memchr(s, 'a', 4));
// 	return (0);
// }