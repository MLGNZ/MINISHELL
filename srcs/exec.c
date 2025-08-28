/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/27 19:17:08 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		cd(pls->cmd_args[0], &ms);
	else if (!ft_strncmp(pls->cmd, "env", ft_strlen(pls->cmd)))
		env(ms);
	return (1);
}

char **lst_to_tab(t_list *env)
{
	t_list *curr;
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

int	exec_cmd(t_pl **pls, t_ms *ms)
{
	pid_t pid;
	int status;
	char **tab_env;
	
	while (*pls)
	{
		if ((*pls)->redir)
		{
			redirect_fds(*pls);
		}
		else
		{
			(*pls)->current_pipe[0] = 0;
			(*pls)->current_pipe[1] = 1;
		}
		if (is_build_in((*pls)->cmd))
		{
			exec_build_in(*pls, ms);
			(*pls)++;
			continue ;
		}
		pid = fork();
		if (!pid)
		{
			tab_env = lst_to_tab(ms->lst_env);
			execve((*pls)->cmd, (*pls)->cmd_args, tab_env);
			perror("execve");
			// exit(errno);
		}
		else if (pid > 0)
			waitpid(pid, &status, 0);
		else
			perror("fork");
		(*pls)++;
	}
	return (1);
}