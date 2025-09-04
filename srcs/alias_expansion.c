/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:29:42 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/31 20:18:23 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Counts the number of different strings that are going to be in the char **
int	cw(char *s0, int *len)
{
	char	*s1;
	int		nw;

	nw = 0;
	s1 = (char *)s0;
	while (*s1)
	{
		if (*s1 == ' ')
				s1++;
		else
		{
			nw++;
			s1 += word_length(s0, s1);
		}
	}
	return (*len = nw);
}

static int	make_it_alias_exp(t_ms *ms, char **s, int *i, int ww)
{
	int	len;

	while ((*s)[*i] && ww != (*s)[*i])
	{
		len = 1;
		if (is_meta(&((*s)[*i]), '$', *s))
		{
			if (!replace_token(s, expanded_string(*s, &((*s)[*i]), \
		get_expansion(&((*s)[*i]) + 1, ms->lst_env, ms->lst_vars, ms), &len)))
				return (0);
		}
		*i += len;
	}
	return (1);
}

static int	make_it_alias_exp2(t_ms *ms, char **s, int *i, int ww)
{
	int	len;

	while ((*s)[*i] && ww != (*s)[*i] && which_word(&(*s)[*i], *s) == ' ')
	{
		len = 1;
		if (is_meta(&((*s)[*i]), '$', *s))
		{
			if (!replace_token(s, expanded_string(*s, &((*s)[*i]), \
		get_expansion(&((*s)[*i]) + 1, ms->lst_env, ms->lst_vars, ms), &len)))
				return (0);
		}
		*i += len;
	}
	return (1);
}

int	alias_expansion(t_ms *ms, char **s)
{
	int		len;
	int		i;
	char	ww;

	i = 0;
	len = 0;
	while (s && *s && (*s)[i])
	{
		ww = which_word(&(*s)[i], *s);
		if ((*s)[i] == ' ')
			while ((*s)[i] == ' ')
				i++;
		else if (ww == '\'' && ++i)
			while ((*s)[i] && which_word(&(*s)[i++], *s) != ww)
				(void)i;
		else if (ww == '\"' && ++i)
			make_it_alias_exp(ms, s, &i, ww);
		else
			make_it_alias_exp2(ms, s, &i, ww);
	}
	return (1);
}

int	replace_token(char **string_address, char *expanded_string)
{
	if (!expanded_string)
		return (0);
	// puts(*string_address);
	free(*string_address);
	*string_address = expanded_string;
	return (1);
}
