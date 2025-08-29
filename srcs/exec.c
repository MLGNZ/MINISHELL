/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/29 22:59:50 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_fds(t_pl *pl)
{
	if (!red_in(pl))
		return (0);
	if (!red_out(pl))
		return (0);
	return (1);
}

int	exec_build_in(t_pl *pls, t_ms *ms)
{
	if (!ft_strncmp(pls->cmd, "echo", ft_strlen(pls->cmd)))
		echo(pls->cmd_args);
	// else if (!ft_strncmp(pls->cmd, "exit", ft_strlen(pls->cmd)))
	// 	exit(pls->cmd_args);
	else if (!ft_strncmp(pls->cmd, "pwd", ft_strlen(pls->cmd)))
		pwd(ms);
	else if (!ft_strncmp(pls->cmd, "export", ft_strlen(pls->cmd)))
		ft_export(pls->cmd_args, ms);
	else if (!ft_strncmp(pls->cmd, "unset", ft_strlen(pls->cmd)))
		ft_unset(pls->cmd_args, ms);
	else if (!ft_strncmp(pls->cmd, "cd", ft_strlen(pls->cmd)))
		cd(pls->cmd_args, &ms);
	else if (!ft_strncmp(pls->cmd, "env", ft_strlen(pls->cmd)))
		env(ms);
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

// void	get_prev_pipes(t_pl **pls, int i)
// {
// 	close((pls[i - 1])->current_pipe[1]);
// 	(pls[i])->current_pipe[0] = (pls[i - 1])->current_pipe[0];
// }
//Pour gerer les subshells, il faudra prendre un truc comme ms->fdin et ms->fdout au lieu de stdin et stdout
void	handle_pipe(t_pl *pl)
{
	// static int last_out;
	
	if (pl->position == ALONE)
		return ;
	else if (pl->position == FIRST)
	{
		// last_out = dup(1);
		dup2(pl->current_pipe[1], 1);
		close(pl->current_pipe[1]);
		close(pl->current_pipe[0]);
	}
	else if (pl->position == INTER)
	{
		close(pl->current_pipe[0]);
		dup2(pl->previous_pipe[0], 0);
		close(pl->previous_pipe[0]);
		dup2(pl->current_pipe[1], 1);
	}
	else if (pl->position == LAST)
	{
    	dup2(pl->previous_pipe[0], 0);
   		close(pl->previous_pipe[0]);
    	close(pl->previous_pipe[1]);
		// pl->current_pipe[1] = last_out;
	}
}

int	exec_cmd(t_pl **pls, t_ms *ms)
{
	char	**tab_env;
	int		i;
	int		status;
	(void)ms;
	i = 0;
	// (pls[i])->previous_pipe[1] = 1;
	// (pls[i])->previous_pipe[0] = 0;// check b_zero deja fai
	// printf("nb of pls %i\n", (*pls)->total_of_pipeline);
	while (pls[i])
	{
		// if is in subshell handle here
		if ((pls[i])->position != LAST && (pls[i])->position != ALONE && pipe((pls[i])->current_pipe) == -1)
		{
			perror("pipe");
			return (0);
		}
		if ((pls[i])->redir && (pls[i])->redir[0])
			if (!redirect_fds(pls[i]))
				return (0);
		if (!(pls[i]->cmd))
			return (0);
		if (is_build_in((pls[i])->cmd))
		{
			exec_build_in(pls[i++], ms);
			continue ;
		}
		(pls[i])->pid = fork();
		if (!(pls[i])->pid)
		{
			handle_pipe(pls[i]);
			if ((pls[i])->redir)
			{
				close((pls[i])->current_pipe[1]);
				dup2((pls[i])->current_pipe[0], 0);
				close((pls[i])->current_pipe[0]);
			}
			tab_env = lst_to_tab(ms->lst_env);
			execve((pls[i])->cmd, (pls[i])->cmd_args, tab_env);
			perror("execve");
			panic(ms, 0);
		}
		else if ((pls[i])->pid == -1)
			perror("fork");
		else
		{
			if (i > 0)
			{
				close((pls[i])->previous_pipe[1]);
				close((pls[i])->previous_pipe[0]);
				(pls[i])->previous_pipe[1] = (pls[i - 1])->current_pipe[1];
				(pls[i])->previous_pipe[0] = (pls[i - 1])->current_pipe[0];
			}
		}
		i++;
	}
	i = -1;
	while (pls[++i] && pls[i]->cmd)
		waitpid((pls[i])->pid, &status, 0);
	return (1);
}
