/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:29:42 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 21:12:39 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int replace_token(char **string_address, char *expanded_string);
static char *get_expansion(const char *s0, t_list *env, t_list *var, t_ms *ms);
static char *expanded_string(const char *s0, char *s, char *expansion, int *len);


int is_ambiguous(char *exp)
{
	int	len;

	len = 0;
	if (cw(exp, &len) > 1)
		return (1);
	return (0);
}

void ambiguous_message(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

char which_word(char *s, char *s0)
{
	char ww;
	
	if (is_meta(s, '\'', s0))
		ww = '\'';
	else if (is_meta(s, '\"', s0))
		ww = '\"';
	else
		ww = ' ';
	return (ww);
}

int alias_in_redir(t_ms *ms, char **s)
{
	int len;
	int i;
	char ww;

	i = 0;
	len = 0;
	while (s && *s && (*s)[i])
	{
		ww = which_word(&(*s)[i], *s);
		if ((*s)[i] == ' ')
			while((*s)[i] == ' ')
				i++;
		else if (ww == '\'' && ++i)
			while ((*s)[i] && which_word(&(*s)[i++], *s) != ww)
				(void)i;
		else if (ww == '\"' && ++i)
		{
			while ((*s)[i] && ww != (*s)[i])
			{
				len = 1;
				if (is_meta(&((*s)[i]), '$', *s))
				{
					char *exp = expanded_string(*s, &((*s)[i]), get_expansion(&((*s)[i]) + 1, ms->lst_env, ms->lst_vars, ms), &len);
					if (!exp)
						return (0);
					if (is_ambiguous(exp))
						return (ambiguous_message(*s), 0);
					printf("%s\n", exp);
					if (!replace_token(s, exp))
						return (0);
				}
				i += len;
			}
		}
		else
		{
			while ((*s)[i] && ww != (*s)[i] && which_word(&(*s)[i], *s) == ' ')
			{
				len = 1;
				if (is_meta(&((*s)[i]), '$', *s))
				{
					char *exp = expanded_string(*s, &((*s)[i]), get_expansion(&((*s)[i]) + 1, ms->lst_env, ms->lst_vars, ms), &len);
					if (!exp)
						return (0);
					if (is_ambiguous(exp))
						return (ambiguous_message(*s), 0);
					printf("%s\n", exp);
					if (!replace_token(s, exp))
						return (0);
				}
				i += len;
			}
		}
	}
	return (1);
}

int alias_expansion(t_ms *ms, char **s)
{
	int len;
	int i;
	char ww;

	i = 0;
	len = 0;
	while (s && *s && (*s)[i])
	{
		ww = which_word(&(*s)[i], *s);
		if ((*s)[i] == ' ')
			while((*s)[i] == ' ')
				i++;
		else if (ww == '\'' && ++i)
			while ((*s)[i] && which_word(&(*s)[i++], *s) != ww)
				(void)i;
		else if (ww == '\"' && ++i)
		{
			while ((*s)[i] && ww != (*s)[i])
			{
				len = 1;
				if (is_meta(&((*s)[i]), '$', *s))
				{
					if (!replace_token(s, expanded_string(*s, &((*s)[i]), get_expansion(&((*s)[i]) + 1, ms->lst_env, ms->lst_vars, ms), &len)))
						return (0);
				}
				i += len;
			}
		}
		else
		{
			while ((*s)[i] && ww != (*s)[i] && which_word(&(*s)[i], *s) == ' ')
			{
				len = 1;
				if (is_meta(&((*s)[i]), '$', *s))
				{
					if (!replace_token(s, expanded_string(*s, &((*s)[i]), get_expansion(&((*s)[i]) + 1, ms->lst_env, ms->lst_vars, ms), &len)))
						return (0);
				}
				i += len;
			}
		}
	}
	return (1);
}

static char *expanded_string(const char *s0, char *s, char *expansion, int *len)
{
	int alias_l = 1;
	char *ret;

	while (s && (ft_isalnum(s[alias_l]) || s[alias_l] == '_'))
		alias_l++;
	if (s && s[1] == '?')
		alias_l = 2;
	*len = ft_strlen(expansion);
	ret = malloc(sizeof(char) * ((int)ft_strlen(s0) - alias_l + *len + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s0, (s - s0) + 1);
	ft_strlcat(ret, expansion, (s - s0) + *len + 1);
	ft_strlcat(ret, &s[alias_l], (s - s0) + *len + ft_strlen(&s[alias_l]) + 1);
	free(expansion);
	return (ret);
}

static char *get_expansion(const char *s0, t_list *env, t_list *var, t_ms *ms)
{
	size_t len;
	char *s;

	len = 0;
	s = (char *)s0;

	if (*s == '?')
	{
		char *ret = ft_itoa(ms->prev_exit_code);
		if (!ret)
			return (0);
		return (ret);
	}
	while (ft_isalnum(*s) || *s == '_')
	{
		(len)++;
		s++;
	}
	while (var)
	{
		if (!ft_strncmp(s0, var->content, len) && ft_strlen(var->content) > len + 1 && ((char *)var->content)[len] == '=')
		{
			printf("found\n");
			return (ft_strdup(&((char *)var->content)[len + 1]));
		}
		var = var->next;
	}
	while (env)
	{
		if (!ft_strncmp(s0, env->content, len) && ft_strlen(env->content) > len + 1 && ((char *)env->content)[len] == '=')
		{
			printf("foundenv\n");
			return (ft_strdup(&(env->content)[len + 1]));
		}
		env = env->next;
	}
	return (0);
}

static int replace_token(char **string_address, char *expanded_string)
{
	if (!expanded_string)
		return (0);
	puts(*string_address);
	free(*string_address);
	*string_address = expanded_string;
	return (1);
}