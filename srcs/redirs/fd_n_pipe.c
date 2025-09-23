/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_n_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:26:53 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/23 14:08:06 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_fds(t_pl *pl, t_ms *ms)
{
	int		i;
	t_fd	*tmp;

	tmp = pl->fds;
	i = -1;
	while (pl->redir && pl->redir[++i])
	{
		pl->i = i;
		if (ft_strchr(pl->redir[i], '>') && ft_isdigit(pl->redir[i][0]))
		{
			if (!redirect_out_fd(&pl, pl->redir[i], pl, i))
				return (0);
			if (tmp)
				tmp = tmp->next;
		}
		if ((!ft_strncmp(pl->redir[i], "<<", 2) || \
		!ft_strncmp(pl->redir[i], "<", 1)) && !red_in(pl, ms))
			return (dup2(pl->fd_in, 0), ms->exit_code = 1, 0);
		if ((!ft_strncmp(pl->redir[i], ">>", 2) || \
		!ft_strncmp(pl->redir[i], ">", 1)) && !red_out(pl, ms))
			return (dup2(pl->fd_out, 1), ms->exit_code = 1, 0);
	}
	return (1);
}

void	handle_pipe(t_pl *pl)
{
	if (pl->position == ALONE)
		return ;
	if (pl->position == FIRST && pl->has_red_out)
		return ;
	if (pl->position == LAST && pl->has_red_in)
	{
		close_fds(pl->previous_pipe[0], pl->previous_pipe[1], 0, 0);
		return ;
	}
	if ((pl->position == LAST || pl->position == INTER) && pl->cmd)
	{
		dup2(pl->previous_pipe[0], 0);
		close_fds(pl->previous_pipe[0], pl->previous_pipe[1], 0, 0);
	}
	if ((pl->position == FIRST || pl->position == INTER) && \
	!pl->has_red_out && (pl->cmd || pl->sub_shell))
	{
		dup2(pl->current_pipe[1], 1);
		close_fds(pl->current_pipe[0], pl->current_pipe[1], 0, 0);
	}
}

void	reset_out_fds(t_pl *pl)
{
	t_fd	*tmp;

	tmp = pl->fds;
	while (tmp)
	{
		dup2(tmp->fd_temp, tmp->fd);
		close(tmp->fd_temp);
		tmp = tmp->next;
	}
}

int	handle_fds(t_pl **pls, int i, t_ms *ms)
{
	my_dup2(ms->fd_out, 1, ms->fd_in, 0);
	if (pls[i]->has_red_out && pls[i]->position != ALONE)
		if (dup2(pls[i]->fd_out, 1) == -1)
			return (0);
	if (pls[i]->has_red_in && pls[i]->position != ALONE)
		if (dup2(pls[i]->fd_in, 0) == -1)
			return (0);
	if (i > 0)
		close_fds(pls[i]->previous_pipe[0], pls[i]->previous_pipe[1], 0, 0);
	if (pls[i]->position == FIRST || pls[i]->position == INTER)
	{
		(pls[i + 1])->previous_pipe[0] = pls[i]->current_pipe[0];
		(pls[i + 1])->previous_pipe[1] = pls[i]->current_pipe[1];
	}
	if (pls[i]->position == ALONE)
		my_dup2(pls[i]->fd_in, 0, pls[i]->fd_out, 1);
	close_fds(ms->fd_in, ms->fd_out, pls[i]->fd_in, pls[i]->fd_out);
	return (1);
}

int	handle_redirs(t_ms *ms, t_pl **pls, int *i)
{
	if (pls[*i]->redir && pls[*i]->redir[0])
	{
		if (!redirect_fds(pls[*i], ms))
		{
			ms->exit_code = 1;
			pls[*i]->pid = -1;
			if (!handle_fds(pls, (*i)++, ms))
				return (perror("dup2"), 0);
			return (2);
		}
	}
	return (1);
}
