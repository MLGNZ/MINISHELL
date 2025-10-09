/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:49:52 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 13:17:46 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		go_to_subshell(t_ms *ms, char **s_readline);
void	protect_subshell(t_ms *ms, t_pl **pls, int *i);
int		handle_subshell(t_pl **pls, int *i, t_ms *ms);
int		is_subshell(char **tab);

int	go_to_subshell(t_ms *ms, char **s_readline)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (!pid)
	{
		freesplit(ms->s_readline);
		if (!dup_split(s_readline, &ms->s_readline, 0))
			panic(ms, 52);
		if (ms->lns)
			erase_lines(&(ms->lns));
		minishell(ms, ms->s_readline);
		close(ms->fd_in);
		panic(ms, ms->exit_code);
	}
	if (pid < 0)
		return (0);
	return (pid);
}

void	protect_subshell(t_ms *ms, t_pl **pls, int *i)
{
	freesplit(ms->s_readline);
	if (!dup_split(pls[*i]->raw_pipeline, &ms->s_readline, 0))
		panic(ms, 52);
	if (ms->lns)
		erase_lines(&(ms->lns));
}

int	handle_subshell(t_pl **pls, int *i, t_ms *ms)
{
	char	**s_readline;

	close_fds(pls[*i]->fd_in, pls[*i]->fd_out, 0, 0);
	pls[*i]->pid = fork();
	if (pls[*i]->pid == -1)
		return (perror("fork"), 0);
	else if (!pls[*i]->pid)
	{
		handle_pipe(pls[*i]);
		protect_subshell(ms, pls, i);
		minishell(ms, ms->s_readline);
		close_fds(ms->fd_in, ms->fd_out, pls[*i]->current_pipe[1], 0);
		panic(ms, 0);
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
