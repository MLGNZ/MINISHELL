/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:15:35 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/27 16:49:05 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_arrays_pl(t_pl *pl, char **tb, int cmd_c, int red_c, int var_c);
static void	get_length_of(char **tab, int *op, int *cmd, int *var);
static int	reassign(t_pl *pl, char **tab, int n_o_pls);
// static void	print_split(char **tab);

char **raw_pipeline(char **tb, int len)
{
	char **ret;
	int i;

	i = -1;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (0);
	while (++i < len)
	{
		ret[i] = ft_strdup(tb[i]);
		if (!ret[i])
			return (0); // ?
	}
	ret[i] = NULL;
	return (ret);
}

void update_r_l(t_pl *pl)
{
	free(pl->raw_pipeline[0]);
	int i;

	i = 1;
	while (pl->raw_pipeline[i + 1])
	{
		pl->raw_pipeline[i - 1] = pl->raw_pipeline[i];
		i++;
	}
	free(pl->raw_pipeline[i]);
	pl->raw_pipeline[i] = NULL;
	pl->raw_pipeline[i - 1] = pl->raw_pipeline[i];
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
		return (0); // ?
	printsplit(pl->raw_pipeline);
	if (pl->raw_pipeline[0][0] == '(')
	// if (is_pipeline_subshell(pl, tb))
	{
		pl->sub_shell = 1;
		update_r_l(pl);
		puts("do some subshell shit");
		return (1);
	}
	else
	{
		if (!make_arrays_pl(pl, tb, 0, 0, 0))
			return (0);
		if (!reassign(pl, tb, n_o_pls))
			return (0);
	}
	return (1);
}

static int	make_arrays_pl(t_pl *pl, char **tb, int cmd_c, int red_c, int var_c)
{
	get_length_of(tb, &red_c, &cmd_c, &var_c);
	if (cmd_c)
	{
		pl->cmd_args = malloc(sizeof(char *) * (cmd_c + 1)); //removed +1
		if (!pl->cmd_args)
			return (0);
		*pl->cmd_args = NULL;
	}
	else
		pl->cmd_args = NULL;
	if (red_c)
	{
		pl->redir = malloc(sizeof(char *) * (red_c * 2 + 1));
		if (!pl->redir)
			return (free(pl->cmd_args), 0);
		*pl->redir = NULL;
	}
	else
		pl->redir = NULL;
	if (var_c)
	{
		pl->var = malloc(sizeof(char *) * (var_c + 1));
		if (!pl->var)
			return (0);
		*pl->var = NULL;
	}
	else
		pl->var = NULL;
	return (1);
}


int is_var_ass(char *str)
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

//dois aussi calculer la taille de l'array de variables
//donc si pas operateur, regarder si bonne structure pour alias etc.
//faire fonction is variable_assignation
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
		else if (!i || !which_op(tab[i - 1])) //always true ?
			(*cmd)++;
	}
}

//devra aussi reassigner vers array of vars
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
		else if ((redir1 == pl->redir && cmd_args1 == pl->cmd_args && n_o_pls == 1) && is_var_ass(tab[i]))
		{
			// ft_lstadd_back(&pl->lst_var, ft_lstnew(ft_strdup(tab[i]))); //////laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
			*(var1) = ft_strdup(tab[i]);
			if (!(*(var1++)))
				return (0);
		}
		else if (!i || !which_op(tab[i - 1])) //always true
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

// static void	print_split(char **tab)
// {
// 	if (!tab)
// 		printf("none");
// 	while (tab && *tab)
// 		printf("[%s] ", *tab++);
// 	printf("\n");
// }
