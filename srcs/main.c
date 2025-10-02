/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:26:22 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/02 18:19:50 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

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
	int		i;
	char	*content;
	t_list	*temp_list;
	
	content = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!content)
		return (ft_lstclear(p_lst, free), 0);
	temp_list = ft_lstnew(content);
	if (!temp_list)
		return (ft_lstclear(p_lst, free), free(content), 0);
	ft_lstadd_back(p_lst, temp_list);
	if (!add_new_elem(p_lst, content, "SHLVL=1") || !add_new_elem(p_lst, content, "_=/usr/bin/env"))
		return (ft_lstclear(p_lst, free), free(content), 0);
	return (1);
}

int	tab_to_lst(char **tab, t_list **p_lst)
{
	char	*content;
	t_list	*temp_list;

	while (tab && *tab)
	{
		content = ft_strdup(*tab);
		if (!content)
			return (ft_lstclear(p_lst, free), 0);
		temp_list = ft_lstnew(content);
		if (!temp_list)
			return (ft_lstclear(p_lst, free), free(content), 0);
		ft_lstadd_back(p_lst, temp_list);
		tab++;
	}
	return (1);
}

void	incr_shlvl(t_list **env, t_ms *ms)
{
	char	*val;
	char *new_sh;
	char *shlvl;
	t_list *sh_lst;

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

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	((void)argc, (void)argv, ft_bzero(&ms, sizeof(t_ms)));
	if (!tab_to_lst(envp, &ms.lst_env))
		return (ft_putstr_fd("Malloc error\n", 2), 1);
	if (!ms.lst_env)
		fill_new_env(&ms.lst_env);
	// else
	// 	incr_shlvl(&ms.lst_env, &ms);
	ms.fd_in = dup(0);
	ms.fd_out = dup(1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	while (1)
	{
		if (!get_valid_line_inter(&ms, -1))
			break ;
		if (ms.s_readline)
			ms.prev_exit_code = minishell(&ms, ms.s_readline);
	}
	close(ms.fd_in);
	close(ms.fd_out);
	panic(&ms, ms.exit_code);
	return (0);
}

int	minishell(t_ms *ms, char **s_readline)
{
	ms->s_readline = s_readline;
	ms->lns = split_and_init_lines(ms, ms->s_readline);
	dive_into_lines(ms, ms->lns);
	return (ms->exit_code);
}
