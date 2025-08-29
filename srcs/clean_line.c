/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:25:28 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/29 04:09:18 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		remove_quotes(const char *s0, char *s);
static int	cat_over_quotes(const char *s0, char *s, char q);
void		remove_backslashes(const char *s0, char *s);

int	clean_expand_in_array(char **tab0, char ***tab_addr, t_ms *ms, int type)
{
	char	**tab;

	tab = tab0;
	while (tab && *tab)
	{
		if (((tab == tab0) || which_op(*(tab - 1)) != HDOC) && \
		!manage_aliases(ms, tab, type))
			return (0);
		tab++;
	}
	if (type == CMD_LT && !update_tab(&tab0, tab0, 0))
		return (0);
	tab = tab0;
	while (tab && *tab)
	{
		remove_quotes(*tab, *tab);
		remove_backslashes(*tab, *tab);
		tab++;
	}
	*tab_addr = tab0;
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
