/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_init_pipelines2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 03:25:57 by tchevall          #+#    #+#             */
/*   Updated: 2025/10/09 12:03:20 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_subshell(char **tab)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (tab && tab[0][0] == '(')
	{
		while (tab && tab[(++i) + 1])
		{
			if (tab[i][0] == '(')
				c++;
			if (tab[i][0] == ')')
				c--;
			if (c < 0)
				return (0);
		}
		if (tab[i][0] == ')')
			return (1);
	}
	return (0);
}




