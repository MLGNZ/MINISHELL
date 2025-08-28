/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:34:55 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/07 16:12:04 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		length(long long ln);

char	*ft_itoa(int n)
{
	char		*ret0;
	char		*ret;
	int			l;
	long long	ln;

	ln = n;
	l = length(ln);
	ret0 = malloc(sizeof(char) * (l + 1));
	if (!ret0)
		return (0);
	ret = ret0 + l;
	*ret = 0;
	if (ln < 0)
	{
		*ret0 = '-';
		ln *= -1;
	}
	while (ln >= 10)
	{
		*(--ret) = (ln % 10) + '0';
		ln /= 10;
	}
	*(--ret) = (ln) + '0';
	return (ret0);
}

static int	length(long long ln)
{
	int	l;

	l = 1;
	if (ln < 0)
	{
		ln *= -1;
		l++;
	}
	while (ln >= 10)
	{
		ln /= 10;
		l++;
	}
	return (l);
}

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (0);
// 	printf("result: %s\n", ft_itoa(ft_atoi(argv[1])));
// 	return (0);
// }