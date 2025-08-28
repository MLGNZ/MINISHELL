/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:43:42 by mlagniez          #+#    #+#             */
/*   Updated: 2025/06/09 11:59:30 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	c;

	c = 0;
	while (s && *s++)
		c += 1;
	return (c);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%ld\n", ft_strlen("   "));
// 	return (0);
// }