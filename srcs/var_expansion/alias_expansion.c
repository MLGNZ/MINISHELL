/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:29:42 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 19:35:06 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			alias_expansion(t_ms *ms, char **s);
static int	make_it_alias_exp(t_ms *ms, char **s, int *i, int ww);
static int	make_it_alias_exp2(t_ms *ms, char **s, int *i, int ww);

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
				return (panic(ms, 52), 0);
		}
		*i += len;
	}
	(*i)++;
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
				return (panic(ms, 52), 0);
		}
		*i += len;
	}
	return (1);
}
