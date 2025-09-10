/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:10:30 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/09 17:25:58 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_len_of(char *s)
{
	int	len;

	len = 0;
	while (s && *(s++) && ++len)
		if (*s == '=')
			return (len);
	return (len);
}

char	*is_already_in(char **splt, char *s)
{
	int	key_len;

	while (splt && *(splt))
	{
		key_len = key_len_of(s);
		if (key_len && !ft_strncmp(*splt, s, key_len) && \
		(*splt)[key_len] == '=')
			return (*splt);
		splt++;
	}
	return (0);
}

static int	split_len(char **splt1, char **splt2)
{
	int	len;

	len = 0;
	while (splt1 && *splt1)
		if (!is_already_in(splt2, *(splt1++)))
			len++;
	return (len);
}

int	update_split_needed(char **splt1, char **splt2, char **ret0, char **ret)
{
	int	i;

	i = -1;
	while (splt1 && splt1[++i])
	{
		*ret = is_already_in(splt2, splt1[i]);
		if (!*ret)
			*ret = ft_strdup(splt1[i]);
		else
			*ret = ft_strdup(*ret);
		if (!*ret)
			return (freesplit(ret0), 0);
		ret++;
	}
	i = -1;
	while (splt2 && splt2[++i])
	{
		if (!is_already_in(splt1, splt2[i]))
		{
			*(ret) = ft_strdup(splt2[i]);
			if (!*(ret++))
				return (freesplit(ret0), 0);
		}
	}
	return (1);
}

char	**update_split(char ***ret_addr, char **splt1, char **splt2)
{
	int		i;
	char	**ret;
	char	**ret0;

	i = 0;
	i += split_len(splt1, 0);
	i += split_len(splt2, splt1);
	ret0 = malloc(sizeof(char *) * (i + 1));
	if (!ret0)
		return (NULL);
	ret = ret0;
	if (!update_split_needed(splt1, splt2, ret0, ret))
		return (NULL);
	*ret = NULL;
	if (*ret_addr == splt1)
	{
		freesplit(splt1);
		splt1 = NULL;
	}
	*ret_addr = ret0;
	return (ret0);
}
