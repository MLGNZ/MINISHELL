/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:12:27 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:23:51 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//char ft_toupper_new(unsigned int i, char *c);

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char	*s0;

	s0 = s;
	while (*s)
	{
		f(s - s0, s);
		s++;
	}
}

// void ft_toupper_new(unsigned int i, char *c)
// {
// 	if (i % 4)
// 		ft_toupper(*c);
// }

// #include <stdio.h>

// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	return (0);
// 	ft_striteri((argv[1]), ft_toupper_new);
// 	printf("%s\n", argv[1]);
// 	return (1);
// }