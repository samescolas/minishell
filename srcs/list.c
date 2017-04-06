/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:36:24 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

t_tkn	*create_list_item(void *data, size_t size)
{
	t_tkn	*ret;

	ret = (void *)0;
	if (data == NULL)
		return (ret);
	if ((ret = (t_tkn *)malloc(sizeof(t_tkn))))
	{
		if ((ret->data = (void *)malloc(size + 1)))
		{
			ft_bzero(ret->data, size + 1);
			ft_memcpy(ret->data, data, size);
		}
		ret->size = size;
		ret->next = NULL;
	}
	return (ret);
}

void	append_list(t_tkn **list, t_tkn *node)
{
	t_tkn	*tmp;

	tmp = (void *)0;
	if (!list || !*list)
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	tmp = (void *)0;
}

void	push_list(t_tkn **list, t_tkn *node)
{
	if (!list || !*list)
		*list = node;
	else
	{
		node->next = *list;
		*list = node;
	}
}

t_tkn	*pop_list(t_tkn **list)
{
	t_tkn	*ret;

	ret = (void *)0;
	if (!list || !*list)
		return (ret);
	ret = *list;
	*list = (*list)->next;
	return (ret);
}
