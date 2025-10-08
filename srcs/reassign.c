/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reassign.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:57:37 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 18:51:13 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir_reass(char **redir1, char **tab, int i);
static int	is_cmd_reass(char **cmd_args1, char **tab, int i);
static int	var_conditions_met(t_pl *pl, char **redir, char **cmd, int nop);
static int	dup_and_add_tab_reass(char *str, char **tab_spot);

int	reassign(t_pl *pl, char **tab, int n_o_pls, int i)
{
	char	**cmd_args1;
	char	**redir1;
	char	**var1;

	cmd_args1 = pl->cmd_args;
	redir1 = pl->redir;
	var1 = pl->var;
	while (tab[++i] && *tab[i] != '|')
	{
		if (is_redir_reass(redir1, tab, i) \
		&& (!dup_and_add_tab_reass(tab[i++], redir1++) \
		|| !dup_and_add_tab_reass(tab[i], redir1++)))
			return (0);
		else if (var_conditions_met(pl, redir1, cmd_args1, n_o_pls) \
		&& is_var_ass(tab[i]))
		{
			if (!dup_and_add_tab_reass(tab[i], var1++))
				return (0);
		}
		else if (is_cmd_reass(cmd_args1, tab, i) \
		&& !dup_and_add_tab_reass(tab[i], cmd_args1++))
			return (0);
	}
	return (1);
}

static int	is_redir_reass(char **redir1, char **tab, int i)
{
	if (redir1 && which_op(tab[i]))
		return (1);
	return (0);
}

static int	var_conditions_met(t_pl *pl, char **redir, char **cmd, int nop)
{
	return (redir == pl->redir && cmd == pl->cmd_args && nop == 1);
}

static int	is_cmd_reass(char **cmd_args1, char **tab, int i)
{
	if (cmd_args1 && (!i || !which_op(tab[i - 1])))
		return (1);
	return (0);
}

static int	dup_and_add_tab_reass(char *str, char **tab_spot)
{
	*tab_spot = ft_strdup(str);
	if (!*tab_spot)
		return (0);
	*(tab_spot + 1) = NULL;
	return (1);
}
