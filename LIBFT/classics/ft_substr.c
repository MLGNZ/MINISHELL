/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:37:31 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:22:04 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (ft_strlen(s) <= start || ft_strlen(s) == 0)
		len = 0;
	else if (ft_strlen(s) - len < start || ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	if (len != 0)
		ft_strlcpy(ret, s + start, len + 1);
	else
		*ret = 0;
	return (ret);
}

// #include <stdio.h>
// #include <string.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 4)
// 		return (1);
// //	printf("OG: %s\n", substr(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3])));
// 	printf("ML: %s\n", ft_substr(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3])));
// 	return (1);
// }