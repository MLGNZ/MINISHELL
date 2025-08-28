/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:45:42 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/07 16:20:00 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	c;

	c = 0;
	if (lst)
		c++;
	while (lst && (*lst).next)
	{
		c++;
		lst = (*lst).next;
	}
	return (c);
}

// #include <stdio.h>

// int	main()
// {
// 	t_list	*one;
// 	t_list	*two;
// 	t_list	*three;
// 	t_list	**lst;

// 	three = ft_lstnew(ft_strdup("3"));
// 	two = ft_lstnew(ft_strdup("2"));
// 	one = ft_lstnew(ft_strdup("1"));
// 	lst = &one;
// 	ft_lstadd_front(lst, two);
// //	ft_lstadd_front(lst, three);
// 	printf("%d\n", ft_lstsize(*lst));
// }