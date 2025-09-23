/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 03:11:16 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/16 18:44:41 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_supertab(char ***tab, int free_strings)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (free_strings)
			freesplit(tab[i]);
		else
			free(tab[i]);
	}
	free(tab);
}

void	update_tab_needed(char **ret, char ***supertab, char **ret0)
{
	int	i;
	int	j;

	ret = ret0;
	i = -1;
	while (supertab[++i])
	{
		j = -1;
		while ((supertab[i][++j]))
			*(ret++) = supertab[i][j];
	}
	*ret = 0;
}

int	update_tab_needed2(int *superlen, char **tab, char ***supertab, int i)
{
	int	len;

	len = 0;
	while (tab && tab[++(i)])
	{
		supertab[i] = ft_split_op(tab[i], &len);
		if (!len)
			len = 1;
		if (!supertab[i])
			return (free_supertab(supertab, 1), 0);
		if (!len)
			len = 1;
		*superlen += len;
	}
	supertab[i] = NULL;
	return (1);
}

int   	update_tab(char ***tab_address, char **tab, int i)
{
	char	***supertab;
	char	**ret0;
	int		superlen;

	superlen = 0;
	while (tab && tab[i])
		i++;
	if (!i)
		return (1);
	supertab = malloc(sizeof(char **) * (i + 1));
	if (!supertab)
		return (0);
	update_tab_needed2(&superlen, tab, supertab, -1);
	ret0 = malloc(sizeof(char *) * (superlen + 1));
	if (!ret0)
		return (free_supertab(supertab, 1), 0);
	update_tab_needed(NULL, supertab, ret0);
	if (!*ret0)
	{
		free(ret0);
		ret0 = NULL;
	}
	freesplit(*tab_address);
	return (*tab_address = ret0, free_supertab(supertab, 0), 1);
}

int	manage_aliases(t_ms *ms, char **tab, int type)
{
	if (type == CMD_LT)
		alias_expansion(ms, tab);
	if (type == REDIR && !alias_in_redir(ms, tab))
		return (0);
	if (type == VAR)
		alias_expansion(ms, tab);
	return (1);
}
