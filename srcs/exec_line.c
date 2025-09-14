/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:57:26 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/12 16:40:33 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_lst_remove(t_list *to_rem, t_list **p_list, int free_content)
{
	t_list	*list;

	if (!to_rem || !*p_list)
		return ;
	list = *p_list;
	if (list == to_rem)
	{
		*p_list = list->next;
		if (free_content)
			free(to_rem->content);
		free(to_rem);
		return ;
	}
	while (list && list->next)
	{
		if (list->next == to_rem)
		{
			list->next = to_rem->next;
			if (free_content)
				free(to_rem->content);
			free(to_rem);
		}
		list = list->next;
	}
}

static int	update_vars(t_ms *ms, t_line *line)
{
	update_lst(&ms->lst_env, &line->lst_vars);
	update_lst(&ms->lst_vars, &line->lst_vars);
	ft_lstadd_back(&ms->lst_vars, line->lst_vars);
	line->lst_vars = NULL;
	return (1);
}
