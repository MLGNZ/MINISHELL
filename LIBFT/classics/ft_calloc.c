/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:22:50 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/07 16:07:47 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ret;
	size_t			n;

	n = nmemb * size;
	if (nmemb && n / nmemb != size)
		return (0);
	ret = malloc(n);
	if (!ret)
		return (0);
	while (n--)
		*ret++ = 0;
	return (ret - (nmemb * size));
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s;

// 	s = ft_calloc(42, sizeof(int));
// 	printf("%s\n", s);
// 	return (0);

// }