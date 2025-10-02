/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/02 18:19:23 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(int pos, t_ms *ms)
{
	t_list	*curr;
	int		i;

	if (pos == -1)
		return (getcwd(NULL, 0));
	curr = ms->lst_env;
	i = -1;
	while (++i < pos)
		curr = curr->next;
}

int	is_valid_var_key(char *str)
{
	if (*str == '=' || ft_isdigit(*str) || !*str)
		return (0);
	while (str && *str && *str != '=' && *str != '+')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	if (*str == '+' && *(str + 1) && *(str + 1) != '=')
		return (0);
	return (1);
}

char	*invalid_key(char *var)
{
	int	i;

	i = -1;
	while (var && var[++i])
		if (var[i] == '+' || var[i] == '=')
			var[i] = 0;
	return (var);
}

void	remove_invalid_arguments(t_list **args, t_ms *ms)
{
	t_list	*temp;

	temp = *args;
	while (temp)
	{
		if (!is_valid_var_key(temp->content))
		{
			ms->exit_code = 1;
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd((char *)temp->content, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ft_lst_remove(temp, args, 1);
			return ;
		}
		else
			temp = temp->next;
	}
}

int	ft_export(char **args, t_ms *ms)
{
	t_list	*lst_args;
	t_list	*lst_vars;

	lst_vars = ms->lst_vars;
	lst_args = NULL;
	if (!*(++args))
		return (1);
	if (!tab_to_lst(args, &lst_args))
		return (panic(ms, 52));
	remove_invalid_arguments(&lst_args, ms);
	update_vars_from_export_args(&lst_args, &ms->lst_vars);
	update_lst(&lst_args, &ms->lst_vars);
	update_lst(&ms->lst_env, &lst_args);
	ft_lstadd_back(&ms->lst_env, lst_args);
	return (1);
}
