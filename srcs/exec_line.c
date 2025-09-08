/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:57:26 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/08 11:46:48 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_vars(t_ms *ms, t_line *line);

/*At the end of this function, what do I have malloc'd ?
	- NOT the t_ln structure, be careful to free everuthing before exiting THIS FUNCTION
		and to get everything you want to get from it before it dissapears
	- an array of pipelines
		- its t_pl pipelines
			-its array of commands (cmd_args)
			-its array of redirections
	- the line char ** that contains every splited word, everything should be freed from this one as it is really convenient;
		NOTE: I'll have to modify most of those strings in order to expend filenames, aliases and remove quotes.
		NOTE: I stored the length of this array to make the freeing easier, even if a malloc fail in the middle, I just have to free up to split_line_length;
	- ms->readline
	*/
/*Je pars avec une ligne de type split issue de mon split op
Une ligne est soit d@limit@ par des operateurs && || ; et contenant des pipelines
Soit c'est un subshell, auquel cas je dois lancer la fonction subshell
Si c'est une ligne, je rentrer dans pipelines qui va creer les pipelines
Puis les cleaner
En sortant de pipelines, je devrais pouvoir executer la ligne directement en dessous*/

int	exec_line(t_ms *ms, t_line *line)
{
	t_pl	**pls;

	pls = line->pls;
	if (line->ctrl_op == AND && ms->prev_exit_code)
		return (1);
	else if (line->ctrl_op == OR && !ms->prev_exit_code)
		return (1);
	if (line->sub_shell)
		go_to_subshell(ms, line->split_line);
	else
	{
		update_vars(ms, line);
		exec_cmd(pls, ms);
		ms->prev_exit_code = ms->exit_code;
	}
	return (1);
}

/*remove an element from a list and reconnect the list*/
void	ft_lst_remove(t_list *to_rem, t_list **p_list, int free_content)
{
	t_list	*list;

	if (!to_rem || !*p_list)
		return ;
	list = *p_list;
	if (list == to_rem)
	{
		*p_list = list->next;
		if (free_content)
			free(to_rem->content);
		free(to_rem);
		return ;
	}
	while (list && list->next)
	{
		if (list->next == to_rem)
		{
			list->next = to_rem->next;
			if (free_content)
				free(to_rem->content);
			free(to_rem);
		}
		list = list->next;
	}
}

// /*for an identical key, update its value in a and remove it from b*/
// void update_lst(t_list **p_lst_a, t_list **p_lst_b)
// {
// 	t_list *env;
// 	t_list *temp;

// 	env = *p_lst_a;
// 	while (env)
// 	{
// 		temp = exists_in_vars((char *)env->content, *p_lst_b);
// 		if (temp)
// 		{
// 			free(env->content);
// 			env->content = temp->content;
// 			temp->content = NULL;
// 			ft_lst_remove(temp, p_lst_b, 0);
// 		}
// 		env = env->next;
// 	}
// }

/*replace dans liste ms->env les elements de la liste ls->vars avec meme truc et les delete de la liste 2
	Ajoute le reste de la liste ls->vars a celle de la liste ms->vars*/
static int	update_vars(t_ms *ms, t_line *line)
{
	update_lst(&ms->lst_env, &line->lst_vars);
	update_lst(&ms->lst_vars, &line->lst_vars);
	ft_lstadd_back(&ms->lst_vars, line->lst_vars);
	line->lst_vars = NULL;
	return (1);
}
