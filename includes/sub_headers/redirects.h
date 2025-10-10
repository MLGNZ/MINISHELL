/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:52:57 by tchevall          #+#    #+#             */
/*   Updated: 2025/10/10 10:53:48 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H
# include "../minishell.h"

int		red_in(t_pl *pipeline, t_ms *ms);
int		pipe_needed(t_pl *pl);
void	reset_out_fds(t_pl *pl);
void	handle_pipe(t_pl *pl);
int		handle_fds(t_pl **pls, int i, t_ms *ms);
void	my_dup2(int fd1, int fd2, int fd3, int fd4);
int		red_out(t_pl *pl);
void	close_fds(int *fd1, int *fd2, int *fd3, int *fd4);
int		handle_redirs(t_ms *ms, t_pl **pls, int *i);
int		redirect_out_fd(t_pl **pl, char *redir, t_pl *temp, int i);
int		look_hd(t_pl *pl, int last[3], t_ms *ms);

#endif