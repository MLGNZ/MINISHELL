/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 03:08:14 by tchevall          #+#    #+#             */
/*   Updated: 2025/10/08 19:36:29 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			alias_in_redir(t_ms *ms, char **s);
static int	make_it(t_ms *ms, char **s, int ww, int *i);
static int	make_it2(t_ms *ms, char **s, int ww, int *i);

int	alias_in_redir(t_ms *ms, char **s)
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
		else if (ww == '\"' && ++i && !make_it(ms, s, ww, &i))
			return (0);
		else if (!make_it2(ms, s, ww, &i))
			return (0);
	}
	return (1);
}

static int	make_it(t_ms *ms, char **s, int ww, int *i)
{
	int		len;
	char	*exp;

	while ((*s)[*i] && ww != (*s)[*i])
	{
		len = 1;
		if (is_meta(&((*s)[*i]), '$', *s))
		{
			exp = expanded_string(*s, &((*s)[*i]), \
		get_expansion(&((*s)[*i]) + 1, ms->lst_env, ms->lst_vars, ms), &len);
			if (!exp)
				return (panic(ms, 52), 0);
			if (is_ambiguous(exp))
				return (free(exp), ambiguous_message(*s), 0);
			replace_token(s, exp);
		}
		*i += len;
	}
	return (1);
}

static int	make_it2(t_ms *ms, char **s, int ww, int *i)
{
	int		len;
	char	*exp;

	while ((*s)[*i] && ww != (*s)[*i] && which_word(&(*s)[*i], *s) == ' ')
	{
		len = 1;
		if (is_meta(&((*s)[*i]), '$', *s))
		{
			exp = expanded_string(*s, &((*s)[*i]), \
		get_expansion(&((*s)[*i]) + 1, ms->lst_env, ms->lst_vars, ms), &len);
			if (!exp)
				return (panic(ms, 52), 0);
			if (is_ambiguous(exp))
				return (free(exp), ambiguous_message(*s), 0);
			replace_token(s, exp);
		}
		*i += len;
	}
	return (1);
}
