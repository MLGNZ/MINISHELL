/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:25:28 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 12:10:28 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			clean_expand_in_array(char **tab0, char ***tab_addr, t_ms *ms, int type);
static int	clean_ex_in_array2(char **t0, t_list **lst, char ***t_adr, int type);

int	clean_expand_in_array(char **tab0, char ***tab_addr, t_ms *ms, int type)
{
	char	**tab;
	t_list	*lst_wc;

	lst_wc = NULL;
	tab = tab0;
	while (tab && *tab)
	{
		if (((tab == tab0) || which_op(*(tab - 1)) != HDOC) && \
		!manage_aliases(ms, tab, type))
			return (*tab_addr = tab0, 0);
		tab++;
	}
	if (type == CMD_LT && !update_tab(&tab0, tab0, 0))
		return (*tab_addr = tab0, panic(ms, 52), 0);
	tab = tab0;
	while (tab && *tab)
	{
		if (((tab == tab0) || which_op(*(tab - 1)) != HDOC) && \
		!manage_wildcards(ms, tab, type, &lst_wc))
			return (0);
		tab++;
	}
	if (!clean_ex_in_array2(tab0, &lst_wc, tab_addr, type))
		return (panic(ms, 52), 0);
	return (1);
}

static int	clean_ex_in_array2(char **t0, t_list **lst, char ***t_adr, int type)
{
	char	**t;

	if (*lst)
	{
		freesplit(t0);
		t0 = lst_to_tab(*lst);
		if (!t0)
			return (ft_lstclear(lst, free), 0);
		ft_lstclear(lst, nothing);
		*t_adr = t0;
	}
	else
	{
		t = t0;
		while (t && *t)
		{
			remove_quotes(*t, *t);
			remove_backslashes(*t, *t);
			t++;
		}
		*t_adr = t0;
	}
	return (1);
}
