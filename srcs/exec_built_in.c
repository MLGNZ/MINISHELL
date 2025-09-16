/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:31:16 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/15 17:42:53 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_dup2(int fd1, int fd2, int fd3, int fd4)
{
	dup2(fd1, fd2);
	dup2(fd3, fd4);
}

static void	handle_cd(t_pl *pl, t_ms *ms)
{
	if (pl->cmd_args[1] && pl->cmd_args[2])
	{
		ms->exit_code = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
	}
	else
		cd(pl->cmd_args, &ms);
}

static int	exec_build_in(t_pl *pl, t_ms *ms, int in_child)
{
	if (!ft_strncmp(pl->cmd, "echo", ft_strlen(pl->cmd)))
		echo(pl->cmd_args, ms);
	else if (!ft_strncmp(pl->cmd, "exit", ft_strlen(pl->cmd)))
		ft_exit(ms, pl->cmd_args);
	else if (!ft_strncmp(pl->cmd, "pwd", ft_strlen(pl->cmd)))
		pwd(ms);
	else if (!ft_strncmp(pl->cmd, "export", ft_strlen(pl->cmd)))
		ft_export(pl->cmd_args, ms);
	else if (!ft_strncmp(pl->cmd, "unset", ft_strlen(pl->cmd)))
		ft_unset(pl->cmd_args, ms);
	else if (!ft_strncmp(pl->cmd, "cd", ft_strlen(pl->cmd)))
		handle_cd(pl, ms);
	else if (!ft_strncmp(pl->cmd, "env", ft_strlen(pl->cmd)))
		env(ms);
	if (in_child)
	{
		close_fds(pl->fd_in, pl->fd_out, ms->fd_in, ms->fd_out);
		exit(0);
	}
	return (1);
}

static int	piped_built_in(t_pl **pls, t_ms *ms, int *i)
{
	(pls[*i])->pid = fork();
	if (pls[*i]->pid == -1)
		return (perror("fork"), 0);
	if (!(pls[*i])->pid)
	{
		handle_pipe(pls[*i]);
		exec_build_in(pls[*i], ms, 1);
	}
	else
	{
		dup2(ms->fd_in, 0);
		if (pls[*i]->fds)
			reset_out_fds(pls[*i]);
		if (!handle_fds(pls, (*i)++, ms))
			return (0);
	}
	return (1);
}

int	handle_built_in(t_pl **pls, int *i, t_ms *ms)
{
	if (pls[*i]->position == ALONE)
	{
		handle_pipe(pls[*i]);
		if (pls[*i]->redir && pls[*i]->has_red_in)
		{
			dup2(pls[*i]->current_pipe[0], 0);
			close_fds(pls[*i]->current_pipe[1], pls[*i]->current_pipe[0], 0, 0);
		}
		exec_build_in(pls[*i], ms, 0);
		dup2(pls[*i]->fd_in, 0);
		dup2(pls[*i]->fd_out, 1);
		if (pls[*i]->fds)
			reset_out_fds(pls[*i]);
		close_fds(pls[*i]->fd_in, pls[(*i)++]->fd_out, 0, 0);
	}
	else
		if (piped_built_in(pls, ms, i))
			return (0);
	return (2);
}
