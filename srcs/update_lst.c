/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:05:35 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/25 16:29:05 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cat_vars(char *var1, char *var2, int free2)
{
	char	*to_cat;
	char	*ret;

	to_cat = var2;
	while (to_cat && *to_cat)
	{
		to_cat++;
		if (*(to_cat - 1) == '=')
			break ;
	}
	ret = malloc(sizeof(char) * (ft_strlen(to_cat) + ft_strlen(var1) + 1));
	if (!ret)
		return (0);
	*ret = 0;
	ft_strlcat(ret, var1, ft_strlen(var1) + 1);
	ft_strlcat(ret, to_cat, ft_strlen(var1) + ft_strlen(to_cat) + 1);
	free(var1);
	if (free2)
		free(var2);
	return (ret);
}

int	update_list_needed(int cat, t_list *env, t_list *temp, t_list **p_lst_b)
{
	if (cat)
	{
		env->content = cat_vars(env->content, temp->content, 1);
		if (!env->content)
			return (0);
	}
	else
	{
		free(env->content);
		env->content = temp->content;
	}
	temp->content = NULL;
	ft_lst_remove(temp, p_lst_b, 0);
	return (1);
}

/*for an identical key, update its value in a and remove it from b*/
//change donc proteger ses appels
int	update_lst(t_list **p_lst_a, t_list **p_lst_b)
{
	t_list	*env;
	t_list	*temp;
	int		cat;

	cat = 0;
	env = *p_lst_a;
	while (env)
	{
		temp = exists_in_vars((char *)env->content, *p_lst_b, &cat);
		if (temp)
			if (!update_list_needed(cat, env, temp, p_lst_b))
				return (0);
		env = env->next;
	}
	return (1);
}

int	size_of_key(char *content)
{
	int	len;

	len = 0;
	while (content && *content && *content != '=' && *content != '+')
	{
		len++;
		content++;
	}
	return (len);
}

t_list	*exists_in_vars(char *content, t_list *vars, int *cat)
{
	int	sok;

	*cat = 0;
	sok = size_of_key(content);
	while (vars)
	{
		if (!ft_strncmp(vars->content, content, sok) && \
	(((char *)vars->content)[sok] == '=' || \
	((char *)vars->content)[sok] == '+'))
		{
			if (((char *)vars->content)[sok] == '+')
				*cat = 1;
			return (vars);
		}
		vars = vars->next;
	}
	return (NULL);
}
