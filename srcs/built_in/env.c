/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:27:59 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/04 18:38:14 by tchevall         ###   ########.fr       */
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

void	pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}

void	ft_exit(t_ms *ms, char **cmd_args)
{
	int	exit_code;
	int	i;

	i = -1;
	if (!cmd_args[1])
		exit(0);
	if (cmd_args[2])
	{
		ft_putstr_fd(" too many arguments", 2);
		ms->exit_code = 1;
		return ;
	}
	while(cmd_args[1][++i])
	{
		while (cmd_args[1][i] == '\"' || cmd_args[1][i] == '+' || cmd_args[1][i] == '-')
			i++;
		if (!ft_isdigit(cmd_args[1][i]))
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			ms->exit_code = 2;
			return ;
		}
	}
	exit_code = ft_atoi(cmd_args[1]);
	exit(exit_code);
}
