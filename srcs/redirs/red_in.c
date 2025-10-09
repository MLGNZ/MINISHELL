/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/26 12:49:53 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
last[0] = last_in_pos;
last[1] = last_hd_pos
last[2] = last_hd_fd
*/
int	red_in(t_pl *pl, t_ms *ms)
{
	static int	last[3];

	if (!pl->i)
	{
		last[0] = -1;
		last[1] = -1;
		last[2] = -1;
	}
	if (!pl->redir)
		return (1);
	if (!look_hd(pl, last, ms))
		return (ms->exit_code = 1, 0);
	if (last[1] != -1 && last[2] != -1 && last[1] > last[0])
	{
		if (pl->cmd)
			if (dup2(last[2], 0) == -1)
				return (perror("dup2"), close(last[2]), 0);
		close(last[2]);
	}
	return (1);
}
