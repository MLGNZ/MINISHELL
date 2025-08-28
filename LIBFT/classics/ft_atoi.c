/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:49:25 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 15:54:22 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*n;
	int		s;
	int		ret;

	ret = 0;
	n = (char *)nptr;
	s = 1;
	while (*n == ' ' || (*n >= 9 && *n <= 13))
		n++;
	if (*n == '-')
	{
		s = -1;
		n++;
	}
	else if (*n == '+')
		n++;
	while (ft_isdigit(*n))
		ret = ret * 10 + (*n++ - '0');
	return (ret * s);
}

// #include <stdlib.h>
// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (1);
// 	printf("OG: %d\n", atoi(*++argv));
// 	printf("ML: %d\n", ft_atoi(*argv));
// 	return (0);
// }