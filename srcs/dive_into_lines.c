/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dive_into_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:11:44 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 13:09:12 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dive_into_lines(t_ms *ms, t_line **lns)
{
	int	i;

	i = -1;
	while (lns && lns[++i])
	{
		if (!split_and_init_pipelines(ms, lns, i))
			return (0);
		if (!exec_line(ms, lns[i]))
		{
			ms->exit_code = g_sig;
			g_sig = 0;
			break ;
		}
	}
	erase_lines(&(ms->lns));
	return (1);
}
