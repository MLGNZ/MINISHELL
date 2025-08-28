/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:27:59 by tchevall          #+#    #+#             */
/*   Updated: 2025/08/27 19:15:27 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_get_env(char *var, t_list *env)
{
	int	i;
	t_list *curr;
	
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
	t_list *curr;

	curr = ms->lst_env;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
			printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
}

void	pwd(t_ms *ms)
{
	if (my_get_env("PWD=", ms->lst_env) != -1)
		printf("%s\n", get_var(my_get_env("PWD=", ms->lst_env), ms));
	else
		printf("PWD=%s\n", get_var(my_get_env("PWD=", ms->lst_env), ms));
}

