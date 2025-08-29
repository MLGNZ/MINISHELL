/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:28:32 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/29 03:41:55 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
utilise int	which_op(char *str)
C.a.d
Pour >> : (which_op(\le char * de la redirection\) == AROUT)
Pour >  : (which_op(\le char * de la redirection\)) == ROUT)
*/

#include "minishell.h"

static int	handle_outfile(t_pl *pl, int out_pos, int is_last)
{
	int		fd;
	char	*out_file;

	out_file = pl->redir[out_pos + 1];
	fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(out_file), 0);
	if (is_last)
		if (dup2(fd, 1) == -1)
			return (perror("dup2"), close(fd), 0);
	close(fd);
	return (1);
}

static int	handle_append(t_pl *pl, int out_pos, int is_last)
{
	int		fd;
	char	*out_file;

	out_file = pl->redir[out_pos + 1];
	fd = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(out_file), 0);
	if (is_last)
		if (dup2(fd, 1) == -1)
			return (perror("dup2"), close(fd), 0);
	close(fd);
	return (1);
}

int	red_out_loop(t_pl *pl, int *last_out_pos, int *last_is_append)
{
	int	i;

	i = -1;
	while (pl->redir[++i])
	{
		if (!ft_strncmp(pl->redir[i], ">>", 2))
		{
			*last_out_pos = i;
			*last_is_append = 1;
			if (!handle_append(pl, i, 0))
				return (0);
		}
		else if (!ft_strncmp(pl->redir[i], ">", 1))
		{
			*last_out_pos = i;
			*last_is_append = 0;
			if (!handle_outfile(pl, i, 0))
				return (0);
		}
	}
	return (1);
}

int	red_out(t_pl *pl)
{
	int	i;
	int	last_out_pos;
	int	last_is_append;

	if (!pl->redir)
		return (1);
	i = -1;
	last_out_pos = -1;
	last_is_append = 0;
	if (!red_out_loop(pl, &last_out_pos, &last_is_append))
		return (0);
	if (last_out_pos != -1)
	{
		if (last_is_append)
			return (handle_append(pl, last_out_pos, 1));
		else
			return (handle_outfile(pl, last_out_pos, 1));
	}
	return (1);
}
