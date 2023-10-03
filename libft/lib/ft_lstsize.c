/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:10:35 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:40:38 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

int	ft_lstsize(t_list	*lst)
{
	int		i;
	t_list	*node;

	i = 0;
	node = lst;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}
/*
#include<stdio.h>
int	main(void)
{
	int		a;
	int		b;
	t_list	*node;
	t_list	**lst;

	lst = malloc(sizeof(node));
	a = 42;
	b = 24;
	node = ft_lstnew(&a);
	*lst = NULL;
	ft_lstadd_front(lst, node);
	node = ft_lstnew(&b);
	ft_lstadd_front(lst, node);
	printf("%i\n", ft_lstsize(*lst));
	free(node);
	free(lst);
	return (0);
}*/