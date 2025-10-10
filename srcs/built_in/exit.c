/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:05:45 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/10 16:00:09 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_exit(t_ms *ms, char **cmd_args, int in_child);
static int	check_errors(char **cmd_args, t_ms *ms);

/*The  exit  status shall be n, if specified,
except that the behavior is unspecified if n is not an unsigned 
decimal integer or is greater than 255.  Otherwise,
the  value  shall  be the exit value of the last command executed, or zero if no
command was executed. When exit is executed in a trap action, the  last  command
is considered to be the command that executed immediately preceding the trap ac‐
tion.*/
void	ft_exit(t_ms *ms, char **cmd_args, int in_child)
{
	long long int	exit_code;

	if (!cmd_args[1])
	{
		if (!in_child)
			ft_putstr_fd("exit\n", 2);
		panic(ms, 0);
	}
	exit_code = ft_atoi(cmd_args[1]);
	if (!in_child && !ms->og_shlvl)
		ft_putstr_fd("exit\n", 2);
	check_errors(cmd_args, ms);
	if (ms)
	{
		freesplit(ms->s_readline);
		ft_lstclear(&ms->lst_env, free);
		ft_lstclear(&ms->lst_vars, free);
		if (ms->lns)
			erase_lines(&(ms->lns));
	}
	exit(exit_code);
}

static int	check_errors(char **cmd_args, t_ms *ms)
{
	int	i;

	i = -1;
	while (cmd_args[1][++i])
	{
		while (cmd_args[1][i] == '\"' || \
		cmd_args[1][i] == '+' || cmd_args[1][i] == '-')
			i++;
		if (!ft_isdigit(cmd_args[1][i]))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			panic(ms, 2);
		}
	}
	if (cmd_args[2])
	{
		ft_putstr_fd("minishell :", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		panic(ms, 1);
	}
	return (1);
}
