/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arrays_in_pipelines.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:30:01 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 12:22:09 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			make_arrays_pl(t_pl **pl, char **tb);
static void	get_length_of(char **tab, int *op, int *cmd, int *var);
static int	malloc_shit(char ***tab, int size);

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

static int	malloc_shit(char ***tab, int size)
{
	*tab = malloc(sizeof(char *) * (size + 1));
	if (!*tab)
		return (0);
	**tab = NULL;
	return (1);
}
