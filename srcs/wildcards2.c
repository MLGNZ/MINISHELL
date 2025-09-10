/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:11:57 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/09 18:16:34 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wildcards_expansion(char **s)
{
	int		first_n_last;
	char	**wild_requ;
	char	*ret;

	first_n_last = 0;
	if (!s)
		return (1);
	wild_requ = get_wild_pattern(s, &first_n_last);
	ret = every_matching_files(wild_requ, first_n_last);
	if (!ret)
		return (1);
	free(*s);
	*s = ret;
	return (1);
}

int	wildcards_in_redir(char **s)
{
	int		first_n_last;
	char	**wild_requ;
	char	*ret;

	first_n_last = 0;
	if (!s)
		return (1);
	wild_requ = get_wild_pattern(s, &first_n_last);
	ret = every_matching_files(wild_requ, first_n_last);
	if (!ret)
		return (1);
	if (is_ambiguous(ret))
		return (ambiguous_message(*s), 0);
	free(*s);
	*s = ret;
	return (1);
}

int	manage_wildcards(char **tab, int type)
{
	if (type == CMD_LT && !wildcards_expansion(tab))
		return (0);
	if (type == REDIR && !wildcards_in_redir(tab))
		return (0);
	if (type == VAR && !wildcards_expansion(tab))
		return (0);
	return (1);
}

int	match_wild_pattern(char *d_name, char **wild_pattern, int first_n_last)
{
	int	i;

	if (!wild_pattern || !*wild_pattern || !d_name)
		return (0);
	i = 0;
	if (first_n_last == 1 || first_n_last == 3)
	{
		if (!ft_strncmp(wild_pattern[i], d_name, ft_strlen(wild_pattern[i])))
			d_name += ft_strlen(wild_pattern[i++]);
		else
			return (0);
	}
	while (*d_name && wild_pattern[i])
	{
		if (!ft_strncmp(wild_pattern[i], d_name, ft_strlen(wild_pattern[i])))
			d_name += ft_strlen(wild_pattern[i++]);
		else
			d_name++;
	}
	if (first_n_last == 2 || first_n_last == 3)
	{
		if (*d_name || wild_pattern[i])
			return (0);
	}
	return (1);
}

char	*wild_join(char *src, char *d_name)
{
	int		size;
	char	*ret;

	ret = NULL;
	size = ft_strlen(src) + ft_strlen(d_name);
	if (src)
	{
		ret = ft_strjoin_free1(src, " ");
		if (!ret)
			return (0);
	}
	else
		ret = NULL;
	ret = ft_strjoin_free1(ret, d_name);
	if (!ret)
		return (0);
	return (ret);
}
