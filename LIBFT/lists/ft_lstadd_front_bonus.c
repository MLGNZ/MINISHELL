/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:32:42 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 18:26:43 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	(*new).next = *lst;
	*lst = new;
}

// #include <stdio.h>
//
// int main()
// {
// 	t_list	*first;
// 	t_list	*new;
// 	t_list	**lst;
//
// 	lst = &first;
// 	first = ft_lstnew("premier");
// 	new = ft_lstnew("nouveau");
// 	printf("before: %s\n", (char *)(*first).content);
// 	ft_lstadd_front(lst, new);
// 	printf("after: %s\n", (char *)(*first).content);
// 	return (0);
// }