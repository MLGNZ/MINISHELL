/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:15:13 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 15:15:57 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../minishell.h"

typedef struct s_ms
{
	t_list			*lst_env;
	t_list			*lst_vars;
	char			*readline;
	char			**s_readline;
	int				s_readline_len;
	struct s_line	**lns;
	unsigned char	prev_exit_code;
	unsigned char	exit_code;
	int				fd_in;
	int				fd_out;
}	t_ms;

typedef struct s_line
{
	struct s_pipeline	**pls;
	t_list				*lst_vars;
	int					nb_of_pls;
	int					ctrl_op;
	int					sub_shell;
	char				**split_line;
	int					split_line_length;
}	t_line;

typedef struct s_fd
{
	int			fd;
	int			fd_temp;
	struct s_fd	*next;
}	t_fd;

typedef struct s_pipeline
{
	char	*cmd;
	char	**cmd_args;
	int		position;
	int		sub_shell;
	char	**redir;
	char	**var;
	t_list	*lst_var;
	char	**raw_pipeline;
	int		total_of_pipeline;
	int		nb_of_this_pipeline;
	t_fd	*fds;
	int		i;
	int		has_error;
	int		has_red_out;
	int		has_red_in;
	int		fd_in;
	int		fd_out;
	int		pid;
	int		previous_pipe[2];
	int		current_pipe[2];
	int		heredoc_pipe[2];
}	t_pl;

#endif