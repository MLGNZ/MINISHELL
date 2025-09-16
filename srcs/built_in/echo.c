/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:25:50 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/15 15:09:00 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n(char **tab)
{
	int	i;
	int	is_n;
	int	not_n;

	i = 1;
	is_n = 0;
	not_n = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], "-n", ft_strlen(tab[i])) && !not_n)
			is_n++;
		else
			not_n = 1;
		i++;
	}
	return (is_n);
}

static char	**get_lines(char **tab)
{
	int		i;
	int		j;
	char	**lines;
	int		to_cpy;

	i = 0;
	to_cpy = 0;
	while (tab[i])
		i++;
	lines = malloc(sizeof(char *) * (i + 1));
	if (!lines)
		return (NULL);
	i = 1;
	j = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "-n", ft_strlen(tab[i])))
			to_cpy = 1;
		if (to_cpy)
			lines[j++] = ft_strdup(tab[i]);
		i++;
	}
	lines[j] = NULL;
	return (lines);
}

static int	write_line(char **line, int option)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_printf("%s", line[i]))
			return (perror("printf"), 1);
		if (line[i++ + 1])
			if (!ft_printf(" "))
				return (perror("printf"), 1);
	}
	if (!option)
		if (!ft_printf("\n"))
			return (perror("printf"), 1);
	return (0);
}

int	echo(char **tab, t_ms *ms)
{
	int		option;
	char	**line;

	if (!tab[1])
	{
		if (!is_n(tab))
			ft_printf("\n");
		return 0;
	}
	option = is_n(tab);
	line = get_lines(tab);
	if (!line)
		return (0);
	ms->exit_code = write_line(line, option);
	if (ms->exit_code)
		return (freesplit(line), 0);
	return (freesplit(line), 1);
}
