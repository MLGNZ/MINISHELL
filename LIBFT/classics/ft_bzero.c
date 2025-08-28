/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:40:55 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 15:55:13 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	while (n-- > 0)
		*s2++ = 0;
	return ;
}

// #include <stdio.h>
// int 	main(void)
// {
// 	int n;
// 	int i;
// 	int	l;

// 	n = 5;
// 	i = 0;
// 	char c[] = "coucou";
// 	l = ft_strlen(c);
// 	ft_bzero(c, n);
// 	while(i < l)
// 		printf("%c\n", c[i++]);
// 	return (0);
// }