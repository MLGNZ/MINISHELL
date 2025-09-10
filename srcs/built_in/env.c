/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:27:59 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/10 19:26:04 by tchevall         ###   ########.fr       */
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

int	is_ok(char **cmd_args, int i)
{
	return (cmd_args[1][i] == '\"' || \
		cmd_args[1][i] == '+' || cmd_args[1][i] == '-');
}

void	ft_exit(t_ms *ms, char **cmd_args)
{
	long long int	exit_code;
	int				i;

	i = -1;
	if (!cmd_args[1])
		exit(0);
	if (cmd_args[2])
	{
		ft_putstr_fd(" too many arguments", 2);
		ms->exit_code = 1;
		return ;
	}
	while (cmd_args[1][++i])
	{
		while (is_ok(cmd_args, i))
			i++;
		if (!ft_isdigit(cmd_args[1][i]))
		{
			ft_putstr_fd("minishell:", 2);
			ft_putstr_fd(cmd_args[1], 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			ms->exit_code = 2;
			return ;
		}
	}
	exit_code = ft_atoi(cmd_args[1]); // mettre atol
	if (exit_code > 2147483647)
	{
		ft_putstr_fd(cmd_args[1], 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		exit(2);
	}
	printf("exit\n");
	exit(exit_code);
}
