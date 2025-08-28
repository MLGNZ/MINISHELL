/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:24:06 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:16:41 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ret;

	ret = (unsigned char *)s;
	while (*ret)
	{
		if (*ret++ == (unsigned char)c)
			return ((char *)--ret);
	}
	if ((unsigned char)c == 0)
		return ((char *)ret);
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 3)
// 		return (0);
// 	//printf("%s\n%c\n", argv[1], argv[2][0]);
// 	printf("%s\n", ft_strchr(argv[1], argv[2][0]));
// 	return (0);
// }