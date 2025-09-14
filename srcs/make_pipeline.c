/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:15:35 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/14 15:38:57 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reassign(t_pl *pl, char **tab, int n_o_pls);

static int	reassign_p1(char **tab, int *i, char ***redir1, int stop)
{
	**(redir1) = ft_strdup(tab[*i]);
	if (!(*(*redir1)++))
		return (0);
	if (!stop)
		(*i)++;
	if (stop)
		return (1);
	**(redir1) = ft_strdup(tab[*i]);
	if (!(*(*redir1)++))
		return (0);
	return (1);
}

static void	set_to_zero(t_pl *pl, char **cmd_args1, char **redir1, char **var1)
{
	if (pl->cmd_args)
		*cmd_args1 = NULL;
	if (pl->redir)
		*redir1 = NULL;
	if (pl->var)
		*var1 = NULL;
}

static int	reassign(t_pl *pl, char **tab, int n_o_pls)
{
	char	**cmd_args1;
	char	**redir1;
	char	**var1;
	int		i;

	i = -1;
	cmd_args1 = pl->cmd_args;
	redir1 = pl->redir;
	var1 = pl->var;
	while (tab[++i] && *tab[i] != '|')
	{
		if (redir1 && which_op(tab[i]) && !reassign_p1(tab, &i, &redir1, 0))
			return (0);
		else if (((redir1 == pl->redir && cmd_args1 == pl->cmd_args && \
		n_o_pls == 1) && is_var_ass(tab[i])) && !reassign_p1(tab, &i, &var1, 1))
			return (0);
		else if (cmd_args1 && (!i || !which_op(tab[i - 1])) && \
		!reassign_p1(tab, &i, &cmd_args1, 1))
			return (0);
		set_to_zero(pl, cmd_args1, redir1, var1);
	}
	return (1);
}

int	make_pipeline(char **tb, t_pl **pl_address, int len, int n_o_pls)
{
	t_pl	*pl;

	pl = malloc(sizeof(t_pl));
	if (!pl)
		return (0);
	ft_bzero(pl, sizeof(t_pl));
	*pl_address = pl;
	pl->raw_pipeline = raw_pipeline(tb, len);
	if (!pl->raw_pipeline)
		return (0);
	printsplit(pl->raw_pipeline);
	if (pl->raw_pipeline[0][0] == '(')
	{
		pl->sub_shell = 1;
		update_r_l(pl);
		return (1);
	}
	else
	{
		if (!make_arrays_pl(&pl, tb))
			return (0);
		if (!reassign(pl, tb, n_o_pls))
			return (0);
	}
	return (1);
}
