/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:25:28 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 15:38:40 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		remove_quotes(const char *s0, char *s);
void		remove_backslashes(const char *s0, char *s);
static int	cat_over_quotes(const char *s0, char *s, char q);

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

void	remove_quotes(const char *s0, char *s)
{
	char	q;

	while (s && *s)
	{
		if (is_meta(s, '\'', (char *)s0))
			q = '\'';
		else if (is_meta(s, '\"', (char *)s0))
			q = '\"';
		else
			q = 0;
		if (q)
			s += cat_over_quotes(s, s, q);
		else
			s++;
	}
}

static int	cat_over_quotes(const char *s0, char *s, char q)
{
	int	len;

	len = 0;
	ft_strlcpy(s, s + 1, ft_strlen(s));
	while (*s)
	{	
		if (is_meta(s, q, (char *)s0))
		{
			len = (s - s0);
			break ;
		}
		s++;
	}
	ft_strlcpy(s, s + 1, ft_strlen(s));
	return (len);
}

void	remove_backslashes(const char *s0, char *s)
{
	while (s0 && *s)
	{
		if (*s == '\\')
			ft_strlcpy(s, s + 1, ft_strlen(s + 1) + 1);
		s++;
	}
}
