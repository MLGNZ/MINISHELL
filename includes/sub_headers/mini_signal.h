#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

# include "../minishell.h"

void	sig_handler(int sig);
void	sig_handler_no(int sig);
void	sig_handler_close(int sig);
void	sig_handler_quit(int sig);

#endif