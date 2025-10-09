/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 03:09:25 by tchevall          #+#    #+#             */
/*   Updated: 2025/10/09 18:24:59 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*expanded_string(const char *s0, char *s, char *exp, int *len);
char		*get_expansion(const char *s0, t_list *env, t_list *var, t_ms *ms);
static char	*get_var_exp(const char *s0, t_list *list, size_t len);

int			replace_token(char **string_address, char *expanded_string);

char	*expanded_string(const char *s0, char *s, char *exp, int *len)
{
	int		alias_l;
	char	*ret;

	alias_l = 1;
	while (s && (ft_isalnum(s[alias_l]) || s[alias_l] == '_'))
		alias_l++;
	if (s && (s[1] == '?' || ft_isdigit(s[1])))
		alias_l = 2;
	*len = ft_strlen(exp);
	ret = malloc(sizeof(char) * ((int)ft_strlen(s0) - alias_l + *len + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s0, (s - s0) + 1);
	ft_strlcat(ret, exp, (s - s0) + *len + 1);
	ft_strlcat(ret, &s[alias_l], (s - s0) + *len + ft_strlen(&s[alias_l]) + 1);
	free(exp);
	return (ret);
}

char	*get_expansion(const char *s0, t_list *env, t_list *var, t_ms *ms)
{
	size_t	len;
	char	*s;
	char	*ret;

	len = 0;
	s = (char *)s0;
	if (*s == '?')
		return (ft_itoa(ms->prev_exit_code));
	if (ft_isdigit(*s))
		return (NULL);
	while (ft_isalnum(*s) || *s == '_')
	{
		len++;
		s++;
	}
	if (!len)
		return (ft_strdup("$"));
	ret = get_var_exp(s0, var, len);
	if (ret)
		return (ret);
	return (get_var_exp(s0, env, len));
}

static char	*get_var_exp(const char *s0, t_list *list, size_t len)
{
	while (list)
	{
		if (!ft_strncmp(s0, list->content, len) && \
	ft_strlen(list->content) > len + 1 && ((char *)list->content)[len] == '=')
			return (ft_strdup(&((char *)list->content)[len + 1]));
		list = list->next;
	}
	return (NULL);
}

int	replace_token(char **string_address, char *expanded_string)
{
	if (!expanded_string)
		return (0);
	free(*string_address);
	*string_address = expanded_string;
	return (1);
}
