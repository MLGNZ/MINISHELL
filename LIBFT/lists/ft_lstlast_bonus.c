/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:58:52 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 19:24:34 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	{
		if (!lst)
			return (NULL);
		while ((*lst).next)
			lst = (*lst).next;
		return (lst);
	}
}

// #include <stdio.h>
//
// int	main()
// {
// 	t_list	*one;
// 	t_list	*two;
// 	t_list	*three;
// 	t_list	**lst;
//
// three = ft_lstnew(ft_strdup("3"));
// two = ft_lstnew(ft_strdup("2"));
// one = ft_lstnew(ft_strdup("1"));
// //	lst = &one;
// 	lst = &two;
// //	ft_lstadd_front(lst, two);
// 	ft_lstadd_front(lst, three);
// 	printf("%s\n", (char *)(*ft_lstlast(*lst)).content);
// 	return (0);
// }