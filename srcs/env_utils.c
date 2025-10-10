/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:06:21 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/10 12:24:56 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		my_get_env(char *var, t_list *env);
char	*ft_getenv(char *key, t_ms *ms);
char	*get_var(int pos, t_ms *ms);
int		add_new_elem(t_list **p_lst, char *content, char *var);
int		fill_new_env(t_list **p_lst);

int	my_get_env(char *var, t_list *env)
{
	int		i;
	t_list	*curr;

	i = 0;
	curr = env;
	while (curr)
	{
		if (curr->content)
			if (!ft_strncmp(var, curr->content, ft_strlen(var)))
				return (i);
		curr = curr->next;
		i++;
	}
	return (-1);
}

char	*ft_getenv(char *key, t_ms *ms)
{
	t_list	*env;
	int		key_len;

	key_len = ft_strlen(key);
	env = ms->lst_env;
	while (env)
	{
		if (!ft_strncmp(env->content, key, key_len) && \
		ft_strlen(env->content) > (size_t)key_len && \
		((char *)env->content)[key_len] == '=')
			return (&(((char *)env->content)[key_len + 1]));
		env = env->next;
	}
	return (0);
}

char	*get_var(int pos, t_ms *ms)
{
	t_list	*curr;
	int		i;

	if (pos == -1)
		return (getcwd(NULL, 0));
	curr = ms->lst_env;
	i = -1;
	while (++i < pos)
		curr = curr->next;
	return ((char *)curr->content);
}

int	add_new_elem(t_list **p_lst, char *content, char *var)
{
	t_list	*temp_list;

	content = ft_strdup(var);
	if (!content)
		return (ft_lstclear(p_lst, free), 0);
	temp_list = ft_lstnew(content);
	if (!temp_list)
		return (ft_lstclear(p_lst, free), free(content), 0);
	ft_lstadd_back(p_lst, temp_list);
	return (1);
}

int	fill_new_env(t_list **p_lst)
{
	char	*content;
	t_list	*temp_list;

	content = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!content)
		return (ft_lstclear(p_lst, free), 0);
	temp_list = ft_lstnew(content);
	if (!temp_list)
		return (ft_lstclear(p_lst, free), free(content), 0);
	ft_lstadd_back(p_lst, temp_list);
	if (!add_new_elem(p_lst, content, "SHLVL=1") || \
	!add_new_elem(p_lst, content, "_=/usr/bin/env"))
		return (ft_lstclear(p_lst, free), free(content), 0);
	return (1);
}
