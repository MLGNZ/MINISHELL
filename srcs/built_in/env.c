/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:27:59 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/12 17:53:11 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_get_env(char *var, t_list *env)
{
	int		i;
	t_list	*curr;

	i = 0;
	curr = env;
	while (curr)
	{
		if (curr->content)
			if (!ft_strncmp(var, curr->content, ft_strlen(var)))
				return (i);
		curr = curr->next;
		i++;
	}
	return (-1);
}

void	env(t_ms *ms)
{
	t_list	*curr;

	curr = ms->lst_env;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
			printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
}

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	printf("%s\n", pwd);
	free(pwd);
	return (1);
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
	return (1);
}

/*The  exit  status shall be n, if specified,
except that the behavior is unspecified if n is not an unsigned 
decimal integer or is greater than 255.  Otherwise,
the  value  shall  be the exit value of the last command executed, or zero if no
command was executed. When exit is executed in a trap action, the  last  command
is considered to be the command that executed immediately preceding the trap ac‐
tion.*/
void	ft_exit(t_ms *ms, char **cmd_args)
{
	long long int	exit_code;

	if (!cmd_args[1])
		exit(0);
	if (cmd_args[2])
	{
		ft_putstr_fd(" too many arguments", 2);
		ms->exit_code = 1;
		return ;
	}
	if (!check_errors(cmd_args, ms))
		return ;
	exit_code = ft_atoi(cmd_args[1]);
	printf("exit\n");
	exit(exit_code);
}
