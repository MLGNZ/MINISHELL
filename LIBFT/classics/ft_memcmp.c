/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:34:17 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:14:40 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (n && *ss1++ == *ss2++)
		n--;
	return ((unsigned char)*--ss1 - (unsigned char)*--ss2);
}

// #include <stdio.h>
// #include <string.h>
// int main(int argc, char **argv)
// {
// 	argc = argc;
// 	printf("OG: %i\n", memcmp(argv[1], argv[2], 2));
// 	printf("ML: %i\n", ft_memcmp(argv[1], argv[2], 2));
// 	return (0);
// }