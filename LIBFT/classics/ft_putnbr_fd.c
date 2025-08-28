/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:40:25 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 16:23:23 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	l;

	l = n;
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		l *= -1;
	}
	if (l >= 10)
		ft_putnbr_fd(l / 10, fd);
	ft_putchar_fd((l % 10) + '0', fd);
}

// int	main(void)
// {
// 	ft_putnbr_fd(-0, 0);
// 	return (0);
// }