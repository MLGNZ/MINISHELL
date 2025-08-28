/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:46:56 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/31 16:31:18 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		c;
	va_list	chain;

	c = 0;
	if (!s)
		return (-1);
	va_start(chain, s);
	while (*s)
	{
		if (*s != '%')
			c += ft_putchar_pf(*(s));
		if (*s == '%')
		{
			if (!check_percent(*(s + 1), "cspdiuxX%"))
				return (va_end(chain), -1);
			c += grand_central(check_percent(*(s + 1), "cspdiuxX%"), chain);
			s++;
		}
		s++;
	}
	return (va_end(chain), c);
}

int	ft_putchar_pf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	check_percent(char c, char *s)
{
	while (*s)
	{
		if (c == *s++)
			return (*(s - 1));
	}
	return (0);
}

int	grand_central(char sign, va_list chain)
{
	if (sign == 'c')
		return (ft_putchar_pf(va_arg(chain, int)));
	if (sign == 's')
		return (stringing(va_arg(chain, char *)));
	if (sign == 'p')
		return (hexing_rex(va_arg(chain, unsigned long long), \
		"0123456789abcdef", 1));
	if (sign == 'd' || sign == 'i')
		return (intergering(va_arg(chain, int)));
	if (sign == 'u')
		return (basing(va_arg(chain, unsigned int), "0123456789", 10));
	if (sign == 'x')
		return (basing(va_arg(chain, unsigned int), "0123456789abcdef", 16));
	if (sign == 'X')
		return (basing(va_arg(chain, unsigned int), "0123456789ABCDEF", 16));
	if (sign == '%')
		return (ft_putchar_pf('%'));
	return (0);
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	int fake;
// 	int	real;	
// 	(void)argc;
// 	(void)argv;
// 	// real = printf("%u | %l | %i\n", -255, 255, 24);
// 	// fake = ft_printf("%u | %l | %i\n", -255, 255, 24);
// 	real = printf("%i %c\n", 54, 90);
// 	fake = ft_printf("%i %c\n", 54, 90);
// 	printf("Real: %d\nFake: %d\n", real, fake);
// 	return (1);
// }
