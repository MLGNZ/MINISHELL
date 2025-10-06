/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:25:28 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/06 15:24:08 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		remove_quotes(const char *s0, char *s);
void		remove_backslashes(const char *s0, char *s);
static int	cat_over_quotes(const char *s0, char *s, char q);

static int	clean_expand_in_array2(char **t0, char **t, char ***t_adr, int type)
{
	t = t0;
	while (t && *t)
	{
		remove_quotes(*t, *t);
		remove_backslashes(*t, *t);
		t++;
	}
	*t_adr = t0;
	return (1);
}

int	clean_expand_in_array(char **tab0, char ***tab_addr, t_ms *ms, int type)
{
	char	**tab;

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
		!manage_wildcards(ms, tab, type))
			return (0);
		tab++;
	}
	if (!clean_expand_in_array2(tab0, tab, tab_addr, type))
		return (*tab_addr = tab0, panic(ms, 52), 0);
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
