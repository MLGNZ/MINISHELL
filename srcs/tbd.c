/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:39:02 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 13:20:39 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	get_status(int status, t_ms *ms)
{
	if (WIFEXITED(status))
	{
		ms->exit_code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		ms->exit_code = WTERMSIG(status) + 128;
		if (ms->exit_code == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}
