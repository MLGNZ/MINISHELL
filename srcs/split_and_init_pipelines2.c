/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_init_pipelines2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 03:25:57 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/24 17:23:06 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_subshell(char **tab)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (tab && tab[0][0] == '(')
	{
		while (tab && tab[(++i) + 1])
		{
			if (tab[i][0] == '(')
				c++;
			if (tab[i][0] == ')')
				c--;
			if (c < 0)
				return (0);
		}
		if (tab[i][0] == ')')
			return (1);
	}
	return (0);
}

int	pipeline_len(char **tb)
{
	int	len;
	int	p;
	int	i;

	i = -1;
	p = 0;
	len = 0;
	while (tb && tb[++i])
	{
		if ((!p && *tb[i] == '|'))
			break ;
		len++;
		if (which_op(tb[i]) == O_PAR)
			p++;
		if (which_op(tb[i]) == C_PAR)
			p--;
	}
	return (len);
}

void	remove_parenthesis_of_line_subshell(t_line *line)
{
	int	i;

	free(line->split_line[0]);
	i = 1;
	while (line->split_line[i + 1])
	{
		line->split_line[i - 1] = line->split_line[i];
		i++;
	}
	free(line->split_line[i]);
	line->split_line[i] = NULL;
	line->split_line[i - 1] = line->split_line[i];
}

int	update_vars_from_export_args(t_list **p_lst_args, t_list **p_lst_vars)
{
	t_list	*lst_vars;
	t_list	*temp;
	int		cat;

	cat = 0;
	lst_vars = *p_lst_vars;
	while (lst_vars)
	{
		temp = exists_in_vars((char *)lst_vars->content, *p_lst_args, &cat);
		if (cat)
		{
			lst_vars->content = cat_vars(lst_vars->content, temp->content, 0);
			if (!lst_vars->content)
				return (0);
		}
		lst_vars = lst_vars->next;
	}
	return (1);
}
