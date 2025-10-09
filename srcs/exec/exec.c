/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 17:11:47 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_errors(t_pl *pl, t_ms *ms)
{
	struct stat	st;

	if (!ft_strchr(pl->cmd, '/'))
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
		if (access(pl->cmd, F_OK))
			panic(ms, 127);
		else
			panic(ms, 126);
	}
}

static int	handle_execve(t_pl *pl, t_ms *ms)
{
	char	**tab_env;

	signal(SIGQUIT, sig_handler_quit);
	handle_pipe(pl);
	close_fds(&(ms->fd_in), &(ms->fd_out), &(pl->fd_in), &(pl->fd_out));
	check_errors(pl, ms);
	tab_env = lst_to_tab(ms->lst_env);
	execve(pl->cmd, pl->cmd_args, tab_env);
	free(tab_env);
	perror("minishell");
	panic(ms, 1);
	return (1);
}

static int	exec_pl(t_pl *pl, t_ms *ms, int *i, t_pl **pls)
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
			handle_execve(pl, ms);
		else if (!handle_fds(pls, (*i)++, ms))
			return (0);
	}
	return (1);
}

static int	exec_loop(t_pl **pls, t_ms *ms)
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

int	exec_cmd(t_pl **pls, t_ms *ms)
{
	int		i;
	int		status;

	status = 0;
	if (!exec_loop(pls, ms))
		return (0);
	i = -1;
	while (pls[++i])
	{
		if (!is_build_in(pls[i]->cmd) || (pls[i]->position != ALONE \
		&& is_build_in(pls[i]->cmd)) || pls[i]->sub_shell)
		{
			if (pls[i]->pid < 0)
			{
				if (pls[i]->pid == -2)
					ms->exit_code = 1;
				continue ;
			}
			signal(SIGINT, sig_handler_no);
			waitpid(pls[i]->pid, &status, 0);
			get_status(status, ms);
		}
		reset_out_fds(pls[i]);
	}
	return (1);
}
