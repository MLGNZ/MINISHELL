/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:24:57 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/23 18:38:18 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_needed(t_pl *pl)
{
	return (pl->position == FIRST || pl->position == INTER);
}

static int	redirect_this_fd(t_pl *pl, int j, char *redir, int i)
{
	char	*out_file;
	int		fd_file;

	out_file = pl->redir[i + 1];
	if (!ft_strncmp(redir + j, ">>", 2))
	{
		fd_file = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_file == -1)
			return (perror(out_file), 0);
		if (dup2(fd_file, pl->fds->fd) == -1)
			return (perror("dup2"), close(fd_file), 0);
	}
	else if (!ft_strncmp(redir + j, ">", 1))
	{
		fd_file = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_file == -1)
			return (perror(out_file), 0);
		if (dup2(fd_file, pl->fds->fd) == -1)
			return (perror("dup2"), close(fd_file), 0);
	}
	return (1);
}

static void	check_and_reset_fd(t_pl *pl, char *redir)
{
	t_fd	*tmp;
	int		fd_num;

	fd_num = ft_atoi(redir);
	tmp = pl->fds;
	while (tmp && tmp->fd != fd_num)
		tmp = tmp->next;
	if (!tmp)
		return ;
	dup2(tmp->fd_temp, tmp->fd);
	close(tmp->fd_temp);
	tmp->fd_temp = dup(tmp->fd);
}

static int	redirect_out_fd2(t_pl **pl, t_fd *new_fd)
{
	t_fd	*last;

	if (!new_fd)
		return (0);
	if (!(*pl)->fds)
		(*pl)->fds = new_fd;
	else
	{
		last = (*pl)->fds;
		while (last->next)
			last = last->next;
		last->next = new_fd;
	}
	return (1);
}

int	redirect_out_fd(t_pl **pl, char *redir, t_pl *temp, int i)
{
	int		j;
	char	*num;
	t_fd	*new_fd;

	j = 0;
	if (!redir || !which_op(redir))
		return (0);
	while (ft_isdigit(redir[j]))
		j++;
	if (redir[j] != '>')
		return (1);
	new_fd = malloc(sizeof(t_fd));
	if (!new_fd)
		return (0);
	new_fd->fd = ft_atoi(redir);
	new_fd->fd_temp = dup(new_fd->fd);
	new_fd->next = NULL;
	if (!redirect_out_fd2(pl, new_fd))
		return (free(new_fd), 0);
	check_and_reset_fd(*pl, redir);
	if (!redirect_this_fd(temp, j, redir, i))
		return (0);
	return (1);
}
