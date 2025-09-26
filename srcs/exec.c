/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/26 13:35:36 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_execve(t_pl *pl, int i, t_ms *ms)
{
	char	**tab_env;
	struct stat st;

	handle_pipe(pl);
	close_fds(ms->fd_in, ms->fd_out, pl->fd_in, pl->fd_out);
	tab_env = lst_to_tab(ms->lst_env);
	if (access(pl->cmd, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pl->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		panic(ms, 127);
	}
	if (!stat(pl->cmd, &st) && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pl->cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		panic(ms, 126);
	}
	if (access(pl->cmd, X_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(pl->cmd);
		panic(ms, 126);
	}
	execve(pl->cmd, pl->cmd_args, tab_env);
	perror("minishell");
	panic(ms, 1);
	return (1);
}

int	exec_pl(t_pl *pl, t_ms *ms, int *i, t_pl **pls)
{
	if (!pls[*i]->cmd)
	{
		handle_pipe(pls[*i]);
		handle_fds(pls, *i, ms);
		pls[*i]->pid = -1;
		(*i)++;
		return (0);
	}
	if (is_build_in(pl->cmd))
		return (handle_built_in(pls, i, ms));
	else
	{
		pl->pid = fork();
		if (pl->pid == -1)
			return (perror("fork"), 0);
		if (!pl->pid)
			handle_execve(pl, *i, ms);
		else if (!handle_fds(pls, (*i)++, ms))
			return (0);
	}
	return (1);
}

int	exec_loop(t_pl **pls, t_ms *ms)
{
	int	i;
	int	redir_val;

	i = 0;
	while (pls[i])
	{
		pls[i]->fd_in = dup(0);
		pls[i]->fd_out = dup(1);
		if (pipe_needed(pls[i]) && pipe(pls[i]->current_pipe) == -1)
			return (perror("pipe"), 0);
		if (pls[i]->sub_shell)
		{
			if (!handle_subshell(pls, &i, ms))
				return (0);
			continue ;
		}
		redir_val = handle_redirs(ms, pls, &i);
		if (redir_val != 1)
			continue ;
		if (g_sig)
			return (0);
		exec_pl(pls[i], ms, &i, pls);
	}
	return (1);
}

static void	get_status(int status, t_ms *ms)
{
	if (WIFEXITED(status))
		ms->exit_code = WEXITSTATUS(status);
}

int	exec_cmd(t_pl **pls, t_ms *ms)
{
	int		i;
	int		status;

	status = 0;
	i = 0;
	if (!exec_loop(pls, ms))
		return (0);
	i = -1;
	while (pls[++i])
	{
		if (!is_build_in(pls[i]->cmd) || \
		(pls[i]->position != ALONE \
		&& is_build_in(pls[i]->cmd)) || pls[i]->sub_shell)
		{
			if (pls[i]->pid == -1)
				continue ;
			if (pls[i]->pid == -2)
			{
				ms->exit_code = 1;
				continue ;
			}
			signal(SIGINT, sig_handler_no);
			waitpid(pls[i]->pid, &status, 0);
			get_status(status, ms);
		}
		signal(SIGINT, sig_handler);
		if (pls[i]->fds)
			reset_out_fds(pls[i]);
	}
	return (1);
}
