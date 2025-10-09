#ifndef TAB_AND_LST_H
# define TAB_AND_LST_H

# include "../minishell.h"

char	**lst_to_tab(t_list *env);
int		tab_to_lst(char **tab, t_list **p_lst);

#endif 