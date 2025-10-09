/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:57:26 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 13:22:45 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_line(t_ms *ms, t_line *line);
static int	update_vars(t_ms *ms, t_line *line);

int	exec_line(t_ms *ms, t_line *line)
{
	t_pl	**pls;
	int		status;
	int		pid;

	pls = line->pls;
	if ((line->ctrl_op == AND && ms->prev_exit_code) || \
	(line->ctrl_op == OR && !ms->prev_exit_code))
		return (1);
	if (line->sub_shell)
	{
		status = 0;
		pid = go_to_subshell(ms, line->split_line);
		if (pid)
			waitpid(pid, &status, 0);
		ms->prev_exit_code = status;
	}
	else
	{
		update_vars(ms, line);
		if (!exec_cmd(pls, ms))
			return (0);
		ms->prev_exit_code = ms->exit_code;
	}
	dup2(ms->fd_in, 0);
	return (1);
}

static int	update_vars(t_ms *ms, t_line *line)
{
	update_lst(&ms->lst_env, &line->lst_vars);
	update_lst(&ms->lst_vars, &line->lst_vars);
	ft_lstadd_back(&ms->lst_vars, line->lst_vars);
	line->lst_vars = NULL;
	return (1);
}
