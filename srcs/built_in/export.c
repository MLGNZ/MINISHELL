/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/27 16:15:23 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_var_key(char *str)
{
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

char *invalid_key(char *var)
{
	int i;

	i = -1;
	while (var && var[++i])
		if (var[i] == '+' || var[i] == '=')
			var[i] = 0;
	return (var);
}

void remove_invalid_arguments(t_list **args)
{
	t_list *temp;

	temp = *args;
	while (temp)
	{
		if (!is_valid_var_key(temp->content))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(invalid_key(temp->content), 2);
			ft_putstr_fd("': not a vaid indentifier", 2);
			ft_lst_remove(temp, args, 1);
		}
		else
			temp = temp->next;
	}
}


// static char *invalid_export_arg(char **args);

/*If no argument specified, the function does not do anything
even though you might think is dispays the list of exported
variables, it is stated nowhere in the export manual that it is
supposed to behave this way*/
int	ft_export(char **args, t_ms *ms)
{
	t_list *lst_args;
	
	if (!args)
		return (1);
	if (!tab_to_lst(args, &lst_args))
		return (panic(ms, 52));
	remove_invalid_arguments(&lst_args);
	update_lst(&ms->lst_env, &lst_args);
	ft_lstadd_back(&ms->lst_env, lst_args);
	return (1);
}

/*Parse the args of export, if any is invalid, it returns it*/
// static char *invalid_export_arg(char **args)
// {
// 	int i;
	
// 	while (args && *args)
// 	{
// 		i = -1;
// 		while ((*args)[++i])
// 		{
// 			if (!ft_isalnum((*args)[i]) && (*args)[i] != '_')
// 				return (*args);
// 		}
// 		args++;
// 	}
// 	return (NULL);
// }