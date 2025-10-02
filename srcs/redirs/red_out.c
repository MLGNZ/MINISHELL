/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:28:32 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/29 18:07:58 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
utilise int	which_op(char *str)
C.a.d
Pour >> : (which_op(\le char * de la redirection\) == AROUT)
Pour >  : (which_op(\le char * de la redirection\)) == ROUT)
*/

#include "minishell.h"

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1)
		close(fd1);
	if (fd2)
		close(fd2);
	if (fd3)
		close(fd3);
	if (fd4)
		close(fd4);
}

static int	handle_outfile(t_pl *pl, int out_pos, int option)
{
	int		fd;
	char	*out_file;

	out_file = pl->redir[out_pos + 1];
	fd = open(out_file, O_WRONLY | O_CREAT | option, 0644);
	if (fd == -1 || access(out_file, W_OK))
		return (ft_putstr_fd("minishell: ", 2), perror(out_file), 0);
	if (dup2(fd, 1) == -1)
		return (ft_putstr_fd("minishell: ", 2), perror("dup2"), close(fd), 0);
	close(fd);
	return (1);
}

int	red_out_loop(t_pl *pl, int *last_out_pos, t_ms *ms)
{
	if (!ft_strncmp(pl->redir[pl->i], ">>", 2))
	{
		pl->has_red_out = 1;
		if (*last_out_pos != -1)
			dup2(pl->fd_out, 1);
		*last_out_pos = pl->i;
		if (!handle_outfile(pl, pl->i, O_APPEND))
			return (0);
	}
	else if (!ft_strncmp(pl->redir[pl->i], ">", 1))
	{
		pl->has_red_out = 1;
		*last_out_pos = pl->i;
		if (*last_out_pos != -1)
			dup2(pl->fd_out, 1);
		if (!handle_outfile(pl, pl->i, O_TRUNC))
			return (0);
	}
	return (1);
}

int	red_out(t_pl *pl, t_ms *ms)
{
	static int	last_out_pos;

	if (!pl->redir)
		return (1);
	last_out_pos = -1;
	if (!red_out_loop(pl, &last_out_pos, ms))
		return (0);
	return (1);
}
