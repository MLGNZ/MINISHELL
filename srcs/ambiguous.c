/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:38:54 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 14:39:30 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous_message(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

int	is_ambiguous(char *exp)
{
	int	len;

	len = 0;
	if (cw(exp, &len) > 1)
		return (1);
	return (0);
}
