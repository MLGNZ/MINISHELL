/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:05:45 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 20:10:08 by mlagniez         ###   ########.fr       */
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
			printf("exit\n");
		exit(0);
	}
	if (!check_errors(cmd_args, ms))
		return ;
	exit_code = ft_atoi(cmd_args[1]);
	if (!in_child)
		printf("exit\n");
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
			ft_putstr_fd("minishell:", 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			ms->exit_code = 2;
			return (0);
		}
	}
	if (cmd_args[2])
	{
		ft_putstr_fd(" too many arguments", 2);
		ms->exit_code = 1;
		return (0);
	}
	return (1);
}
