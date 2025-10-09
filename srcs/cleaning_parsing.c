/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:57:50 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 12:05:02 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			clean_all_pipelines(t_ms *ms, t_line *ln);
static int	clean_pipeline(t_ms *ms, t_line *ln, t_pl *pl, int position);
static int	get_pos_of_pipeline(int position, int n_of_pl);
static void	set_cmd_and_args(t_pl *pl);

int	clean_all_pipelines(t_ms *ms, t_line *ln)
{
	t_pl	**pls;
	int		i;

	i = -1;
	pls = ln->pls;
	while (pls && pls[++i])
		if (!clean_pipeline(ms, ln, pls[i], i))
			return (0);
	return (1);
}

static int	get_pos_of_pipeline(int position, int n_of_pl)
{
	if (!position && position == n_of_pl - 1)
		return (ALONE);
	else if (!position)
		return (FIRST);
	else if (position == n_of_pl - 1)
		return (LAST);
	return (INTER);
}

static void	set_cmd_and_args(t_pl *pl)
{
	if (pl->cmd_args)
		pl->cmd = pl->cmd_args[0];
	else
		pl->cmd = 0;
}

void	lst_print(t_list *lst)
{	
	while (lst)
	{
		puts(lst->content);
		lst = lst->next;
	}
}

static int	clean_pipeline(t_ms *ms, t_line *ln, t_pl *pl, int position)
{
	pl->position = get_pos_of_pipeline(position, ln->nb_of_pls);
	if (pl->sub_shell)
		return (1);
	if (!clean_expand_in_array(pl->cmd_args, &(pl->cmd_args), ms, CMD_LT) \
	|| !clean_expand_in_array(pl->redir, &(pl->redir), ms, REDIR) \
	|| !clean_expand_in_array(pl->var, &(pl->var), ms, VAR))
		return (0);
	find_cmd(pl->cmd_args, ms);
	set_cmd_and_args(pl);
	if (!tab_to_lst(pl->var, &pl->lst_var))
		return (panic(ms, 52), 0);
	if (!update_lst(&ln->lst_vars, &pl->lst_var))
		return (panic(ms, 52), 0);
	ft_lstadd_back(&ln->lst_vars, pl->lst_var);
	pl->lst_var = NULL;
	if (0)
		lst_print(ln->lst_vars);
	return (1);
}
