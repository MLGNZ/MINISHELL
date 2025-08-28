/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_expand_in_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:25:28 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/20 18:18:38 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(const char *s0, char *s);
static int	cat_over_quotes(const char *s0, char *s, char q);
void	remove_backslashes(const char *s0, char *s);

void free_supertab(char ***tab, int free_strings)
{
	int i;

	i = -1;
	while (tab[++i])
	{
		if (free_strings)
			freesplit(tab[i]);
		else
			free(tab[i]);
			// (void)i;
	}
	free(tab);
}

int update_tab(char ***tab_address, char **tab)
{
	char ***supertab;
	int i;
	int len;
	int superlen;
	char **ret;

	(void)tab_address;
	i = 0;
	superlen = 0;
	while (tab && tab[i])
		i++;
	if (!i)
		return (1);
	supertab = malloc(sizeof(char **) * (i + 1));
	if (!supertab)
		return (0);
	i = -1;
	while (tab && tab[++i])
	{
		supertab[i] = ft_split_op(tab[i], &len);
		
		if (!len)
			len = 1;
		if (!supertab[i])
			return (free_supertab(supertab, 1), 0); //freesplitdesupertab
		if (!len)
			len = 1;
		superlen += len;
	}
	supertab[i] = NULL;

	
	
	// printf("superlen %i\n", superlen);

	char **ret0 = malloc(sizeof(char *) * (superlen + 1));
	if (!ret0)
		return (0); //freesplit de supertab
	ret = ret0;	
	i = -1;
	int j;
	while (supertab[++i])
	{
		j = -1;
		while ((supertab[i][++j]))
			*(ret++) = supertab[i][j];
	}
	*ret = 0;
	i = -1;
	// while (supertab[++i])
	// {
	// 	free(*(supertab[i]));
	// }

	
	// printsplit(ret0);
	// printf("end\n");
	// puts("debug");
	printsplit(*tab_address);
	freesplit(*tab_address);
	*tab_address = ret0;
	free_supertab(supertab, 0);
	return (1);
}

// int alias_in_redir(t_ms *ms, const char *s0, char **s)
// {
// 	(void)ms;
// 	(void)s0;
// 	(void)s;
// 	return (1);
// }

int manage_aliases(t_ms *ms, char **tab, int type)
{
	if (type == CMD_LT && !alias_expansion(ms, tab))
		return (0);
	if (type == REDIR && !alias_in_redir(ms, tab))
		return (0);
	if (type == VAR && !alias_expansion(ms, tab))
		return (0);
	return (1);
}

int	clean_expand_in_array(char **tab0, char ***tab_address, t_ms *ms, int type)
{
	/*
	1) alias expansions
	2) remove quotes
	3) remove backslash
	*/
	
	char **tab;
	tab = tab0;
	(void)ms;
	while (tab && *tab)
	{
		
		if (((tab == tab0) || which_op(*(tab - 1)) != HDOC) && !manage_aliases(ms, tab, type))
		// if (type == CMD_LT && !alias_expansion(ms, *tab, tab))
			return (0);
		// remove_quotes(*tab, *tab);
		// remove_backslashes(*tab, *tab);
		tab++;
	}
	if (type == CMD_LT && !update_tab(&tab0, tab0)) //change it when you want to move it
		return (0);
	tab = tab0;
	while (tab && *tab)
	{
		remove_quotes(*tab, *tab);
		remove_backslashes(*tab, *tab);
		tab++;
	}
	*tab_address = tab0;
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


	
	// while (*s && (s == s0 || *(s - 1)))
	// {	
	// 	if (is_meta(s + 1, q, (char *)s0) && q)
	// 	{
	// 		len = (s - s0);
	// 		q = 0;
	// 	}
	// 	*s = *(s + 1 + (!q));
	// 	printf("%s\n", s);
	// 	s++;
	// }
	// *s = 0;
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
