/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/08 18:40:21 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_pl *pl)
{
	if (pl->position == FIRST && pl->has_red_out)
		return ;
	if (pl->position == LAST && pl->has_red_in)
	{
		close(pl->previous_pipe[0]);
		close(pl->previous_pipe[1]);
		return ;
	}
    if (pl->position == LAST || pl->position == INTER)
	{
		dup2(pl->previous_pipe[0], 0);
        close(pl->previous_pipe[0]);
        close(pl->previous_pipe[1]);
	}
	if ((pl->position == FIRST || pl->position == INTER) && !pl->has_red_out)
	{
		dup2(pl->current_pipe[1], 1);
        close(pl->current_pipe[0]);
		close(pl->current_pipe[1]);
    }
}

int	redirect_fds(t_pl *pl, t_ms *ms)
{	
	int	i;

	i = -1;
	while (pl->redir[++i])
	{
		pl->i = i;
		if (ft_isdigit(pl->redir[i][0]))
			if(!redirect_out_fd(pl))
				return (0);
		if (!ft_strncmp(pl->redir[i], "<<", 2) || !ft_strncmp(pl->redir[i], "<", 1))
			if(!red_in(pl, ms))
				return (dup2(pl->fd_in, 0), ms->exit_code = 1, 0);
		if (!ft_strncmp(pl->redir[i], ">>", 2) || !ft_strncmp(pl->redir[i], ">", 1))
			if(!red_out(pl, ms))
				return (0);
	}
	return (1);
}

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
			(ms->exit_code = 1, ft_putstr_fd(" too many arguments", 2));
		cd(pl->cmd_args, &ms);
	}
	else if (!ft_strncmp(pl->cmd, "env", ft_strlen(pl->cmd)))
		env(ms);
	if (in_child)
	{
		close(pl->fd_in);
		close(pl->fd_out);
		exit(0);
	}
	return (1);
}

char	**lst_to_tab(t_list *env)
{
	t_list	*curr;
	char	**tab;
	int		i;

	curr = env;
	i = 0;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	curr = env;
	i = 0;
	while (curr)
	{
		tab[i++] = curr->content;
		curr = curr->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	handle_fds(t_pl **pls, int i)
{
	if (pls[i]->has_red_out && pls[i]->position != ALONE)
		if (dup2(pls[i]->fd_out, 1) == -1)
			return (0);
	if (pls[i]->has_red_in && pls[i]->position != ALONE)
		if (dup2(pls[i]->fd_in, 0) == -1)
			return (0);
	if (i > 0)
	{
		close(pls[i]->previous_pipe[0]);
		close(pls[i]->previous_pipe[1]);
	}
	if (pls[i]->position == FIRST || pls[i]->position == INTER)
	{
		(pls[i + 1])->previous_pipe[0] = pls[i]->current_pipe[0];
		(pls[i + 1])->previous_pipe[1] = pls[i]->current_pipe[1];
	}
	if (pls[i]->position == ALONE)
	{
		dup2(pls[i]->fd_in, 0);
		dup2(pls[i]->fd_out, 1);
	}
	close(pls[i]->fd_in);
	close(pls[i]->fd_out);
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
			if (!handle_fds(pls, (*i)++))
				return (0);
	}
	return (2);
}

int	handle_execve(t_pl **pls, int i, t_ms *ms)
{
	char	**tab_env;

	handle_pipe(pls[i]);
	// if (pls[i]->redir && (!pls[i]->has_red_out && pls[i]->has_red_in) && pls[i]->position != ALONE)
	// {
	// 	close(pls[i]->current_pipe[1]);
	// 	dup2(pls[i]->current_pipe[0], 0);
	// 	close(pls[i]->current_pipe[0]);
	// }
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

int	redirect_this_fd(int fd, t_pl *pl, int i, int j)
{
	char *out_file;
	int		fd_file;

	out_file = pl->redir[i + 1];
	if (!ft_strncmp(pl->redir[i] + j, ">>", 2))
	{
		fd_file = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror(out_file), 0);
		if (dup2(fd_file, fd) == -1)
			return (perror("dup2"), close(fd), 0);
	}
	else if (!ft_strncmp(pl->redir[i] + j, ">", 1))
	{
		fd_file = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(out_file), 0);
		if (dup2(fd_file, fd) == -1)
			return (perror("dup2"), close(fd), 0);
	}
	pl->has_red_out = 1;
	return (1);
}			


int	redirect_out_fd(t_pl *pl)
{
	int i;
	int	j;
	char *num;

	i = 0;
	if(!pl->redir)
		return (0);
	while (pl->redir && pl->redir[i])
	{
		j = 0;
		while(ft_isdigit(pl->redir[i][j]))
			j++;
		if (j)
		{
			num = malloc(sizeof(char) * (j + 1));
			if (!num)
				return (0);
			ft_strlcpy(num, pl->redir[i], j + 1);
			if (!redirect_this_fd(ft_atoi(num), pl, i, j))
				return (free(num), 0);
			free(num);
		}
		i++;
	}
	return (1);
}

void	close_fds(t_pl **pls, int i)
{
	close(pls[i]->current_pipe[0]);
	close(pls[i]->current_pipe[1]);
}

int	handle_redirs(t_ms *ms, t_pl **pls, int *i)
{
	if (pls[*i]->redir && pls[*i]->redir[0])
	{
		if (!redirect_fds(pls[*i], ms) || !redirect_out_fd(pls[*i]))
		{
			if (!handle_fds(pls, (*i)++))
				return (perror("dup2"), 0);
			return (2);
		}
	}
	return (1);
}
int	pipe_needed(t_pl *pl)
{
	return (pl->position == FIRST || pl->position == INTER);
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
		redir_val = handle_redirs(ms, pls, &i);
		if (redir_val == 2)
			continue ;
		else if (!redir_val)
		{
			i++;
			continue;
		}
		if (!pls[i]->cmd)
		{
			close(pls[i]->fd_in);
			close(pls[i]->fd_out);
			i++;
			continue ;
		}
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
		else
			if (!handle_fds(pls, i))
				return (0);
		i++;
	}
	return (1);
}

int	exec_cmd(t_pl **pls, t_ms *ms)
{
	int		i;
	int		status;

	i = 0;
	if (!exec_loop(pls, ms))
		return (0);
	i = -1;
	while (pls[++i] && pls[i]->cmd)
	{
		if (!is_build_in(pls[i]->cmd))
		{
			waitpid(pls[i]->pid, &status, 0);
			if (WIFEXITED(status))
				ms->exit_code = WEXITSTATUS(status);
		}
	}
	return (1);
}
