/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:10:24 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:40:36 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
#include<stdio.h>
int	main(void)
{
	int		a;
	t_list	*node;

	a = 42;
	node = ft_lstnew(&a);
	printf("Content: %i\nPointer: %p\n", *(int*)node->content, node->next);
	free(node);
	return (0);
}*/