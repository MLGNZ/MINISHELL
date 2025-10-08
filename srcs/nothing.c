/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nothing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:38:44 by tchevall          #+#    #+#             */
/*   Updated: 2025/10/08 17:01:32 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nothing(void *whatever)
{
	(void)whatever;
}

void	incr_shlvl(t_list **env, t_ms *ms)
{
	char	*val;
	char	*new_sh;
	char	*shlvl;
	t_list	*sh_lst;

	if (my_get_env("SHLVL", *env) == -1)
		return ;
	shlvl = get_var(my_get_env("SHLVL", *env), ms);
	val = ft_itoa(ft_atoi(shlvl + 6) + 1);
	if (!val)
		panic(ms, 52);
	new_sh = ft_strjoin_free2("SHLVL=", val);
	if (!new_sh)
		panic(ms, 52);
	sh_lst = ft_lstnew(new_sh);
	if (!sh_lst)
		panic(ms, 52);
	if (!update_lst(&ms->lst_env, &sh_lst))
		panic(ms, 52);
}

static char	*emf_loop(char **ret_add, struct dirent *dirent, int is_dir)
{
	char	*ret;

	ret = *ret_add;
	ret = wild_join(ret, (char *)dirent->d_name);
	if (!ret)
		return (NULL);
	if (is_dir)
	{
		ret = ft_strjoin_free1(ret, "/");
		if (!ret)
			return (NULL);
	}
	return (*ret_add = ret);
}

int	emf_loop_in_loop(t_list **list, struct dirent *dirent, int is_dir)
{
	char	*ret;
	t_list	*new;

	ret = ft_strdup((char *)dirent->d_name);
	if (!ret)
		return (0);
	if (is_dir)
	{
		ret = ft_strjoin_free1(ret, "/");
		if (!ret)
			return (0);
	}
	new = ft_lstnew(ret);
	if (!new)
		return (free(ret), 0);
	ft_lstadd_back(list, new);
	return (1);
}