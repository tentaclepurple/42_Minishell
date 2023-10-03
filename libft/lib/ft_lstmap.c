/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:10:07 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:40:33 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

/* void	*ft_strlen2(void *s)
{
	size_t	i;
	size_t	*mal;
	char	*saux;

	i = 0;
	mal = malloc(sizeof(size_t));
	saux = s;
	while (saux[i])
		i++;
	*mal = i;
	return (mal);
} */

static t_list	*ft_lstnew_map(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
	{
		free (content);
		return (NULL);
	}
	node->content = content;
	node->next = NULL;
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_cpy;
	t_list	*new_node;
	t_list	*node;

	if (!lst || !f || !del)
		return (NULL);
	lst_cpy = ft_lstnew_map(f(lst->content));
	if (lst_cpy == NULL)
		return (NULL);
	node = lst_cpy;
	lst = lst->next;
	while (lst)
	{
		new_node = ft_lstnew_map(f(lst->content));
		if (new_node == NULL)
		{
			ft_lstclear(&lst_cpy, del);
			return (NULL);
		}
		node->next = new_node;
		node = node->next;
		lst = lst->next;
	}
	free (lst);
	return (lst_cpy);
}

/* #include<stdio.h>
int	main(void)
{
	t_list	*res;
	t_list	*lst;
	t_list	*save;
	size_t	*i;

	lst = ft_lstnew("one");
	save = lst;
	lst -> next = ft_lstnew("two");
	lst = lst->next;
	lst -> next = ft_lstnew("three");
	lst = lst->next;
	res = ft_lstmap(save, ft_strlen2, free);
	while (res != NULL)
	{
		i = (size_t *)res->content;
		printf("%zu\n", *i);
		res = res->next;
	}
	return (0);
} */
