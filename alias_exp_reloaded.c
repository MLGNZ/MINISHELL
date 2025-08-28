/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_exp_reloaded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:49:35 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/19 17:00:33 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char which_word(char *s, char *s0)
{
	char ww;
	
	if (is_meta(*s, '\'', s0))
		ww = '\'';
	else if (is_meta(*s, '\"', s0))
		ww = '\"';
	else
		ww = ' ';
	return (ww);
}

int alias_expansion(t_ms *ms, const char *s0, char **s)
{
	int len;
	int i;
	char ww;

	i = 0;
	len = 0;
	(void)s0;
	while (s && *s && (*s)[i])
	{
		ww = which_word((*s)[i], *s);
		if (ww == '\'')
			while ((*s)[i] && which_word((*s)[i++], *s) != ww)
				(void)i;
		// if (is_meta(&((*s)[i]), '\'', *s))
		// 	while ((*s)[i++] && !is_meta(&((*s)[i]), '\'', *s))
		// 		i++;
		else
		{
			while ((*s)[i] && which_word((*s)[i++], *s) != ww)
			{
				len = 1;
				if (is_meta(&((*s)[i]), '$', *s))
				{
					if (!replace_token(s, expanded_string(*s, &((*s)[i]), get_expansion(&((*s)[i]) + 1, ms->envp, ms->vars), &len)))
						return (0);
				}
				i += len;
			}
		}
		// if ((*s)[i])
		// 	i++;
	}
	return (1);
}