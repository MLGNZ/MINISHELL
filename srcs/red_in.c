/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/04 18:09:54 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_infile(t_pl *pl, int in_pos)
{
	int		fd;
	char	*in_file;

	if (!pl->redir[in_pos + 1][0])
		return (0);
	in_file = pl->redir[in_pos + 1];
	fd = open(in_file, O_RDONLY);
	if (fd == -1)
		return (perror(in_file), 0);
	if (pl->cmd)
	{
		if (dup2(fd, 0) == -1)
		{
			perror("dup2");
			close(fd);
			return (0);
		}
	}
	close(fd);
	return (1);
}

static int	hd_loop(t_pl **pl, char *delim, int check_free)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0, &check_free);
		if (!line && !check_free)
			return (free(line), 0);
		else if (!line && check_free)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		if (!ft_strncmp(line, delim, ft_strlen(line) + 1))
			return (free(line), 1);
		ft_putstr_fd(line, (*pl)->current_pipe[1]);
		ft_putstr_fd("\n", (*pl)->current_pipe[1]);
		free(line);
	}
	return (1);
}

static int	handle_heredoc(t_pl *pl, int hd_pos)
{
	char	*delim;
	int		check_free;

	check_free = 0;
	delim = pl->redir[hd_pos + 1];
	if (pipe(pl->current_pipe) == -1)
		return (perror("pipe"), 0);
	if (!hd_loop(&pl, delim, check_free))
		return (0);
	close(pl->current_pipe[1]);
	return (1);
}

int	look_hd(t_pl *pl, int *last_in_pos, int *last_hd_pos, int *last_hd_fd)
{
	if (!ft_strncmp(pl->redir[pl->i], "<<", 2))
	{
		pl->has_red_in = 1;
		*last_hd_pos = pl->i;
		if (*last_in_pos < *last_hd_pos)
		{
			dup2(pl->fd_in, 0);
			dup2(pl->fd_out, 1);
		}
		if (!handle_heredoc(pl, pl->i))
			return (0);
		if (*last_hd_fd != -1)
			close(*last_hd_fd);
		*last_hd_fd = dup(pl->current_pipe[0]);
		close(pl->current_pipe[0]);
	}
	else if (!ft_strncmp(pl->redir[pl->i], "<", 1))
	{
		pl->has_red_in = 1;
		*last_in_pos = pl->i;
		if (!handle_infile(pl, *last_in_pos))
			return (0);
	}
	return (1);
}

int	red_in(t_pl *pl, t_ms *ms)
{
	static int	last_in_pos;
	static int	last_hd_pos;
	static int	last_hd_fd;

	if (!pl->i)
	{
		last_in_pos = -1;
		last_hd_pos = -1;
		last_hd_fd = -1;
	}
	if (!pl->redir)
		return (1);
	if (!look_hd(pl, &last_in_pos, &last_hd_pos, &last_hd_fd))
		return (ms->exit_code = 1, 0);
	if (last_hd_pos != -1 && last_hd_fd != -1 && last_hd_pos > last_in_pos)
	{
		if (pl->cmd)
			if (dup2(last_hd_fd, 0) == -1)
				return (perror("dup2"), close(last_hd_fd), 0);
		close(last_hd_fd);
	}
	return (1);
}
