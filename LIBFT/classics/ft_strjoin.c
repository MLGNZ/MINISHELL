/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:08:16 by mlagniez          #+#    #+#             */
/*   Updated: 2025/06/14 18:10:30 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
	ft_strlcat(ret, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (ret);
}

// #include <stdio.h>
// #include <string.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 3)
// 		return (1);
// //	printf("OG: %s\n", substr(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3])));
// 	printf("ML: %s\n", ft_strjoin(argv[1], argv[2]));
// 	return (1);
// }