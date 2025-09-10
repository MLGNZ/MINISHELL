/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:15:35 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/09 18:47:22 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_arrays_pl(t_pl **pl, char **tb);
static void	get_length_of(char **tab, int *op, int *cmd, int *var);
static int	reassign(t_pl *pl, char **tab, int n_o_pls);

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
		if (which_op(tab[i]))
		{
			*(redir1) = ft_strdup(tab[i++]);
			if (!(*(redir1++)))
				return (0);
			*(redir1) = ft_strdup(tab[i]);
			if (!(*(redir1++)))
				return (0);
		}
		else if ((redir1 == pl->redir && cmd_args1 == pl->cmd_args && \
		n_o_pls == 1) && is_var_ass(tab[i]))
		{
			*(var1) = ft_strdup(tab[i]);
			if (!(*(var1++)))
				return (0);
		}
		else if (!i || !which_op(tab[i - 1]))
		{
			*(cmd_args1) = ft_strdup(tab[i]);
			if (!(*(cmd_args1++)))
				return (0);
		}
		if (pl->cmd_args)
			*cmd_args1 = NULL;
		if (pl->redir)
			*redir1 = NULL;
		if (pl->var)
			*var1 = NULL;
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
