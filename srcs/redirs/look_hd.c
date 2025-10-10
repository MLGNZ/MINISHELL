/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:32:57 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/10 14:10:40 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			look_hd(t_pl *pl, int last[3], t_ms *ms);
static int	handle_infile(t_pl *pl, int in_pos);
static int	handle_heredoc(t_pl *pl, int hd_pos, t_ms *ms);
static int	hd_loop(t_pl **pl, char *delim, int check_free, t_ms *ms);
static void	print_error_hd(char *delim);

/*
last[0] = last_in_pos;
last[1] = last_hd_pos
last[2] = last_hd_fd
*/
int	look_hd(t_pl *pl, int last[3], t_ms *ms)
{
	if (!ft_strncmp(pl->redir[pl->i], "<<", 2))
	{
		pl->has_red_in = 1;
		last[1] = pl->i;
		if (last[0] < last[1])
		{
			dup2(pl->fd_in, 0);
			dup2(pl->fd_out, 1);
		}
		if (!handle_heredoc(pl, pl->i, ms))
			return (0);
		if (last[2] != -1)
			close(last[2]);
		last[2] = dup(pl->heredoc_pipe[0]);
		close(pl->heredoc_pipe[0]);
	}
	else if (!ft_strncmp(pl->redir[pl->i], "<", 1))
	{
		pl->has_red_in = 1;
		last[0] = pl->i;
		if (!handle_infile(pl, last[0]))
			return (0);
	}
	return (1);
}

static int	handle_heredoc(t_pl *pl, int hd_pos, t_ms *ms)
{
	char	*delim;
	int		check_free;

	check_free = 0;
	delim = pl->redir[hd_pos + 1];
	if (pipe(pl->heredoc_pipe) == -1)
		return (perror("pipe"), 0);
	if (!hd_loop(&pl, delim, check_free, ms))
		return (signal(SIGINT, sig_handler), 0);
	if (pl->heredoc_pipe[1] != -1)
		close(pl->heredoc_pipe[1]);
	return (1);
}

static int	hd_loop(t_pl **pl, char *delim, int check_free, t_ms *ms)
{
	char	*line;

	signal(SIGINT, sig_handler_close);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0, &check_free);
		if ((!line && !check_free))
		{
			if (!g_sig)
				print_error_hd(delim);
			return (free(line), close((*pl)->heredoc_pipe[1]), \
			close((*pl)->heredoc_pipe[0]), !g_sig);
		}
		else if (!line && check_free)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		if (!ft_strncmp(line, delim, ft_strlen(line) + 1))
			return (free(line), 1);
		alias_expansion(ms, &line);
		ft_putstr_fd(line, (*pl)->heredoc_pipe[1]);
		(ft_putstr_fd("\n", (*pl)->heredoc_pipe[1]), free(line));
	}
	return (panic(ms, 52), close((*pl)->heredoc_pipe[1]), 1);
}

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
	if (access(in_file, R_OK))
	{
		pl->pid = -1;
		return (0);
	}
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

static void	print_error_hd(char *delim)
{
	ft_putstr_fd("\nminishell: warning: ", 2);
	ft_putstr_fd("here-document at current line ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
}
