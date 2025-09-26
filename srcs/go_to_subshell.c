/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:49:52 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/26 11:20:37 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ne pas effacer, si pas change, ajouter waitpid dans le gt subshell in line
int	go_to_subshell(t_ms *ms, char **s_readline)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (!pid)
	{
		minishell(ms, s_readline);
		close(ms->fd_in);
		exit(ms->exit_code);
	}
	if (pid < 0)
		return (0);
	return (pid);
}

int	handle_subshell(t_pl **pls, int *i, t_ms *ms)
{
	close_fds(pls[*i]->fd_in, pls[*i]->fd_out, 0, 0);
	pls[*i]->pid = fork();
	if (pls[*i]->pid == -1)
		return (perror("fork"), 0);
	else if (!pls[*i]->pid)
	{
		handle_pipe(pls[*i]);
		minishell(ms, pls[*i]->raw_pipeline);
		close_fds(ms->fd_in, ms->fd_out, pls[*i]->current_pipe[1], 0);
		exit(0);
	}
	else
	{
		if (pls[*i]->position == FIRST || pls[*i]->position == INTER)
		{
			pls[*i + 1]->previous_pipe[0] = pls[*i]->current_pipe[0];
			pls[*i + 1]->previous_pipe[1] = pls[*i]->current_pipe[1];
		}
		handle_fds(pls, (*i)++, ms);
	}
	return (1);
}
