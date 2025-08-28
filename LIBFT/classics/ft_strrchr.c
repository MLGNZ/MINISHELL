/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:34:42 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:20:17 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*ret;
	unsigned char	*real_ret;

	ret = (unsigned char *)s;
	real_ret = 0;
	while (*ret)
	{
		if (*ret++ == (unsigned char)c)
			real_ret = ret - 1;
	}
	if ((unsigned char)c == *ret)
		return ((char *)ret);
	return ((char *)real_ret);
}

// #include <stdio.h>
// #include <string.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 3)
// 		return (0);
// 	//printf("%s\n%c\n", argv[1], argv[2][0]);
// 	printf("%s\n", strrchr(argv[1], argv[2][0]));
// 	return (0);
// }