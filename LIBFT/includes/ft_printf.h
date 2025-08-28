/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 05:41:26 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/13 18:51:04 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *s, ...);
int	ft_putchar_pf(char c);
int	check_percent(char c, char *s);
int	grand_central(char sign, va_list chain);
int	stringing(char *s);
int	intergering(int nb);
int	basing(unsigned int nb, const char *s, unsigned int l_base);
int	hexing_rex(unsigned long long nb, const char *s, int b);

#endif