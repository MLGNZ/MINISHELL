/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:32:27 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:19:52 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*bigg;

	bigg = (char *)big;
	if (!*little)
		return (bigg);
	while (*bigg && len > 0)
	{
		if (ft_strncmp(little, bigg++, ft_strlen(little)) == 0 && \
		ft_strlen(little) <= len)
			return (--bigg);
		len--;
	}
	return (0);
}

// #include <stdio.h>
// #include <bsd/string.h>

// int	main(int argc, char **argv)
// {
// 	const char *big;
// 	const char *little;
// 	big = argv[1];
// 	little = argv[2];
// 	printf("OG:%s\nML:%s\n", strnstr(big, little, 3), ft_strnstr(big,
//little, 3));

// 	//printf("%s\n", strnstr("bar", "bar", 2));

// 	return(0);
// }