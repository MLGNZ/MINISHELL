/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:04:48 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 15:54:18 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
	{
		*lst = new;
	}
	else
		(*ft_lstlast(*lst)).next = new;
}

// #include <stdio.h>

// int	main()
// {
// 	t_list	*one;
// 	t_list	*two;
// 	t_list	*three;
// 	t_list	**lst;

// three = ft_lstnew(ft_strdup("3"));
// two = ft_lstnew(ft_strdup("2"));
// one = ft_lstnew(ft_strdup("1"));
// 	lst = &one;
// 	ft_lstadd_back(lst, two);
// 	ft_lstadd_back(lst, three);
// 	printf("%s\n", (char *)(*ft_lstlast(*lst)).content);
// 	return (0);
// }