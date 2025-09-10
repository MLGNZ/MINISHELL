/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/10 17:44:13 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_build_in(t_pl *pl, t_ms *ms, int in_child)
{
	if (!ft_strncmp(pl->cmd, "echo", ft_strlen(pl->cmd)))
		echo(pl->cmd_args, ms);
	else if (!ft_strncmp(pl->cmd, "exit", ft_strlen(pl->cmd)))
		ft_exit(ms, pl->cmd_args);
	else if (!ft_strncmp(pl->cmd, "pwd", ft_strlen(pl->cmd)))
		pwd();
	else if (!ft_strncmp(pl->cmd, "export", ft_strlen(pl->cmd)))
		ft_export(pl->cmd_args, ms);
	else if (!ft_strncmp(pl->cmd, "unset", ft_strlen(pl->cmd)))
		ft_unset(pl->cmd_args, ms);
	else if (!ft_strncmp(pl->cmd, "cd", ft_strlen(pl->cmd)))
	{
		if (pl->cmd_args[2])
		{
			ms->exit_code = 1;
			ft_putstr_fd(" too many arguments", 2);
		}
		cd(pl->cmd_args, &ms);
	}
	else if (!ft_strncmp(pl->cmd, "env", ft_strlen(pl->cmd)))
		env(ms);
	if (in_child)
	{
		close(pl->fd_in);
		close(pl->fd_out);
		close(ms->fd_in);
		exit(0);
	}
	return (1);
}

int	handle_built_in(t_pl **pls, int *i, t_ms *ms)
{
	if (pls[*i]->position == ALONE || pls[*i]->position == LAST)
	{
		handle_pipe(pls[*i]);
		if (pls[*i]->redir && pls[*i]->has_red_in)
		{
			close(pls[*i]->current_pipe[1]);
			dup2(pls[*i]->current_pipe[0], 0);
			close(pls[*i]->current_pipe[0]);
		}
		exec_build_in(pls[*i], ms, 0);
		dup2(pls[*i]->fd_in, 0);
		dup2(pls[*i]->fd_out, 1);
		close(pls[*i]->fd_in);
		if (pls[*i]->fds)
			reset_out_fds(pls[*i]);
		close(pls[(*i)++]->fd_out);
	}
	else
	{
		(pls[*i])->pid = fork();
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
	}
	return (2);
}

int	handle_execve(t_pl **pls, int i, t_ms *ms)
{
	char	**tab_env;

	handle_pipe(pls[i]);
	close(ms->fd_in);
	close(ms->fd_out);
	tab_env = lst_to_tab(ms->lst_env);
	if (access(pls[i]->cmd, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pls[i]->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		close(pls[i]->fd_in);
		close(pls[i]->fd_out);
		panic(ms, 127);
	}
	execve(pls[i]->cmd, pls[i]->cmd_args, tab_env);
	perror("minishell");
	panic(ms, 1);
	return (1);
}

int	handle_subshell(t_pl **pls, int *i, t_ms *ms)
{
	handle_pipe(pls[*i]);
	close(pls[*i]->fd_in);
	close(pls[*i]->fd_out);
	if (!go_to_subshell(ms, pls[*i]->raw_pipeline))
		return (perror("fork"), 0);
	handle_fds(pls, *i, ms);
	(*i)++;
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
		if (redir_val == 2)
			continue ;
		else if (!redir_val)
			continue ;
		if (is_build_in(pls[i]->cmd))
		{
			if (handle_built_in(pls, &i, ms) == 2)
				continue ;
			else
				return (0);
		}
		pls[i]->pid = fork();
		if (pls[i]->pid == -1)
			perror("fork");
		if (!pls[i]->pid)
		{
			if (!handle_execve(pls, i, ms))
				return (0);
		}
		else if (pls[i]->pid < 0)
			return (perror("fork"), 0);
		else
			if (!handle_fds(pls, i, ms))
				return (0);
		i++;
	}
	return (1);
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
	while (pls[++i] && pls[i]->cmd)
	{
		if (!is_build_in(pls[i]->cmd) || \
		((pls[i]->position != ALONE && pls[i]->position != LAST) \
		&& is_build_in(pls[i]->cmd)))
		{
			if (pls[i]->pid == -1)
				continue ;
			waitpid(pls[i]->pid, &status, 0);
			if (WIFEXITED(status))
				ms->exit_code = WEXITSTATUS(status);
		}
		if (pls[i]->fds)
			reset_out_fds(pls[i]);
	}
	return (1);
}
