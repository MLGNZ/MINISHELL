/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:27:47 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/27 19:07:49 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_infile(t_pl *pipeline, int in_pos)
{
	int fd;
	char *in_file;

	in_file = pipeline->redir[in_pos + 1];
	fd = open(in_file, O_RDONLY);
	if (fd == -1)
		return (0);
	dup2(fd, pipeline->previous_pipe[0]);
	close(fd);
	return (1);
}

static int	open_hd(t_pl *pipeline, int red, int i, int in_pos)
{
	char	*hd;
	int		check_free;
	char *delim;

	delim = pipeline->redir[i + 1];
	if (red)
		close(pipeline->current_pipe[0]);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		hd = get_next_line(0, &check_free);
		if (!hd && check_free == 1)
			return (free(hd), 0);
		if (!ft_strncmp(delim, hd, ft_strlen(hd) - 1)
			&& ft_strlen(hd) > 1)
			return (free(hd), close(pipeline->current_pipe[1]), 1);
		if (red)
			ft_putstr_fd(hd, pipeline->current_pipe[1]);
		free(hd);
	}
	if (!red)
		handle_infile(pipeline, in_pos);
	return (1);
}

int	red_in(t_pl *pipeline)
{
	int i;
	int hd_pos;
	int	in_pos;

	i = 0;
	hd_pos = -1;
	in_pos = -1;
	while (pipeline->redir[i])
	{
		if (!ft_strncmp(pipeline->redir[i], "<<", ft_strlen(pipeline->redir[i])))
			hd_pos = i;
		else if (!ft_strncmp(pipeline->redir[i], "<", ft_strlen(pipeline->redir[i])))
			in_pos = i;
		i++;
	}
	if (in_pos > hd_pos && hd_pos != -1)
		open_hd(pipeline, 0, hd_pos, in_pos);
	else if (in_pos < hd_pos && hd_pos != -1)
		open_hd(pipeline, 1, hd_pos, in_pos);
	else if (hd_pos == -1 && in_pos != -1)
		if (!handle_infile(pipeline, in_pos))
			return (0);
	return (1);
}

int	redirect_fds(t_pl *pipeline)
{
	if (!red_in(pipeline))
		return (0);
	// if (!red_out(pipeline))
	// 	return (0);
	return (1);
}