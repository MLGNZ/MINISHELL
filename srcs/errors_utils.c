/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:19:24 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/26 16:15:21 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_length_of(char **tab, int *op, int *cmd, int *var)
{
	int	i;

	i = -1;
	while (tab[++i] && *tab[i] != '|')
	{
		if (which_op(tab[i]))
			(*op)++;
		else if ((!*op && !*cmd) && is_var_ass(tab[i]))
			(*var)++;
		else if (!i || !which_op(tab[i - 1]))
			(*cmd)++;
	}
}

int	make_arrays_pl(t_pl **pl, char **tb)
{
	int	cmd_c;
	int	red_c;
	int	var_c;

	cmd_c = 0;
	red_c = 0;
	var_c = 0;
	(*pl)->cmd_args = NULL;
	(*pl)->redir = NULL;
	(*pl)->var = NULL;
	get_length_of(tb, &red_c, &cmd_c, &var_c);
	if (cmd_c && !malloc_shit(&((*pl)->cmd_args), cmd_c))
		return (0);
	if (red_c && !malloc_shit(&((*pl)->redir), red_c * 2))
		return (0);
	if (var_c && !malloc_shit(&((*pl)->var), var_c))
		return (0);
	return (1);
}

int	is_var_ass(char *str)
{
	while (str && *str && *str != '=' && *str != '+')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	if (!*str)
		return (0);
	if (*str == '+' && *(str + 1) && *(str + 1) != '=')
		return (0);
	return (1);
}

void	get_status(int status, t_ms *ms)
{
	if (WIFEXITED(status))
		ms->exit_code = WEXITSTATUS(status);
}
