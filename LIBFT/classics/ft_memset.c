/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:20:03 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:16:30 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	while (n-- > 0)
		*s2++ = (unsigned char)c;
	return (s);
}

// #include <stdio.h>
// int 	main(void)
// {
// 	char c[] = "coucou";
// 	ft_memset(c, 49, 0);
// 	printf("%s\n", c);
// 	return (0);
// }