/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:44:03 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/07 16:18:36 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	ft_toupper_new(unsigned int i, char c);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	char	*ret0;

	ret0 = ft_strdup(s);
	if (!ret0)
		return (0);
	ret = ret0;
	while (*ret)
	{
		*ret = f(ret - ret0, *ret);
		ret++;
	}
	return (ret0);
}

// char ft_toupper_new(unsigned int i, char c)
// {
// 	if (i % 4)
// 		return(ft_toupper(c));
// 	return (c);
// }

// #include <stdio.h>

// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	return (0);
// 	printf("%s\n", ft_strmapi((argv[1]), ft_toupper_new));
// 	return (1);
// }