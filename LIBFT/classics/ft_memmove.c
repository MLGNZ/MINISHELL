/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:17:27 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/23 18:18:02 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (d < s && (dest || src))
	{
		while (n--)
			*d++ = *s++;
	}
	else if (d >= s && (dest || src))
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char s[] = "lorem ipsum dolor";
// 	char *d;//[] = "lorem ipsum";
// 	int	ls;
// 	int	n;
// 	int	i;

// 	i = -1;
// 	n = 5;
// 	d = &s[2];
// 	ls = ft_strlen(s);
// 	ft_memmove(d, s, n);
// 	while (++i < ls)
// 		printf("%c", s[i]);
// 		printf("\n");
// 	return (1);
// }

// void	*ft_memmove(void *dest, const void *src, size_t n)
// {
// 	unsigned char *s;
// 	unsigned char *d;
// 	unsigned char t[n];
// 	size_t	i;

// 	i = -1;
// 	s = (unsigned char *)src;
// 	d = (unsigned char *)dest;
// 	ft_memcpy(t, s, n);
// 	while (++i < n)
// 		*d++ = t[i];
// 	return (dest);
// }

// #include <stdio.h>
// #include <string.h>
// int main ()
// {
// 	char str[] = "123456789";

// 	ft_memmove(str + 2, str, 4);
// 	printf ("%s", str);
// }
