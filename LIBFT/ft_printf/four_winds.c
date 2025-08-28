/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   four_winds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 05:42:28 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/31 16:31:32 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	stringing(char *s)
{
	int	c;

	c = 0;
	if (!s)
		return (write(1, "(null)", 6), 6);
	while (*s)
		c += ft_putchar_pf(*s++);
	return (c);
}

int	intergering(int nb)
{
	int			c;
	long long	l;

	l = (long long)nb;
	c = 0;
	if (l < 0)
	{
		c += ft_putchar_pf('-');
		l *= -1;
	}
	if (l >= 10)
		c += intergering(l / 10);
	c += ft_putchar_pf((l % 10) + '0');
	return (c);
}

int	basing(unsigned int nb, const char *s, unsigned int l_base)
{
	int				c;
	unsigned int	l;

	l = (unsigned int)nb;
	c = 0;
	if (l >= l_base)
		c += basing(l / l_base, s, l_base);
	c += ft_putchar_pf(*(s + (l % l_base)));
	return (c);
}

int	hexing_rex(unsigned long long nb, const char *s, int b)
{
	int	c;

	c = 0;
	if (b == 1)
	{
		if (!nb)
		{
			write(1, "(nil)", 5);
			return (5);
		}
		write(1, "0x", 2);
		c += 2;
	}
	if (nb >= 16)
		c += hexing_rex(nb / 16, s, 0);
	c += ft_putchar_pf((*(s + (nb % 16))));
	return (c);
}
