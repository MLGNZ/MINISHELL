/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_init_pipelines.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:21:32 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 12:03:49 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			split_and_init_pipelines(t_ms *ms, t_line **lns, int i);
static int	count_pipelines(char **tb);
static int	create_pipelines(t_line *line, char **split_line);
static void	remove_parenthesis_of_line_subshell(t_line *line);
static int	pipeline_len(char **tb);

int	split_and_init_pipelines(t_ms *ms, t_line **lns, int i)
{
	t_line	*line;

	line = lns[i];
	if (is_subshell(line->split_line))
	{
		line->sub_shell = 1;
		remove_parenthesis_of_line_subshell(line);
	}
	else
	{
		line->nb_of_pls = count_pipelines(line->split_line);
		line->pls = malloc(sizeof(t_pl) * (line->nb_of_pls + 1));
		if (!line->pls)
			return (panic(ms, 52));
		if (!create_pipelines(line, line->split_line))
			return (panic(ms, 52));
	}
	if (!clean_all_pipelines(ms, line))
		return (0);
	return (1);
}

static int	create_pipelines(t_line *line, char **split_line)
{
	int	i;
	int	j;
	int	p;
	int	len;

	p = 0;
	i = 0;
	j = 0;
	while (split_line[i])
	{
		len = pipeline_len(&(split_line[i]));
		if (!make_pipeline(&split_line[i], &line->pls[j++], \
		len, line->nb_of_pls))
			return (line->pls[j] = NULL, 0);
		i += len;
		if (split_line[i])
			i++;
	}
	line->pls[j] = NULL;
	return (1);
}

static int	count_pipelines(char **tb)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (tb[i])
	{
		count++;
		i += pipeline_len(&(tb[i]));
		if (tb[i])
			i++;
	}
	return (count);
}

static void	remove_parenthesis_of_line_subshell(t_line *line)
{
	int	i;

	free(line->split_line[0]);
	i = 1;
	while (line->split_line[i + 1])
	{
		line->split_line[i - 1] = line->split_line[i];
		i++;
	}
	free(line->split_line[i]);
	line->split_line[i] = NULL;
	line->split_line[i - 1] = line->split_line[i];
}

static int	pipeline_len(char **tb)
{
	int	len;
	int	p;
	int	i;

	i = -1;
	p = 0;
	len = 0;
	while (tb && tb[++i])
	{
		if ((!p && *tb[i] == '|'))
			break ;
		len++;
		if (which_op(tb[i]) == O_PAR)
			p++;
		if (which_op(tb[i]) == C_PAR)
			p--;
	}
	return (len);
}