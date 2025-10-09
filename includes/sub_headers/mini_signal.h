/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:15:22 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 15:15:23 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

# include "../minishell.h"

void	sig_handler(int sig);
void	sig_handler_no(int sig);
void	sig_handler_close(int sig);
void	sig_handler_quit(int sig);

#endif