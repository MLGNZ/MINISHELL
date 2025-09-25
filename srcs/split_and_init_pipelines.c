/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_init_pipelines.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:21:32 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/24 17:22:58 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipelines(char **tb);
static int	create_pipelines(t_line *line, char **split_line);

int			get_previous_data(t_line *line, t_line *previous_line);
void		remove_parenthesis_of_line_subshell(t_line *line);

int	split_and_init_pipelines(t_ms *ms, t_line **lns, int i)
{
	t_line	*line;

	line = lns[i];
	if (i > 1)
		get_previous_data(line, lns[i - 1]);
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
		return (panic(ms, 52));
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

int	get_previous_data(t_line *line, t_line *previous_line)
{
	(void)line;
	(void)previous_line;
	return (0);
}
