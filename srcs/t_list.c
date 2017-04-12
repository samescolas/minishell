/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/10 17:33:36 by sescolas         ###   ########.fr       */
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
		ret->prev = NULL;
		ret->next = NULL;
	}
	return (ret);
}

void	insert_list(t_tkn **list, t_tkn *node, int (*cmp)(t_tkn *, t_tkn *))
{
	t_tkn	*tmp;

	if (!list || !*list)
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next)
		{
			if (cmp(tmp, node) < 0)
				tmp = tmp->next;
			else
			{
				node->prev = tmp->prev;
				node->prev->next = node;
				node->next = tmp->next->next;
				tmp->prev = node;
				break ;
			}
		}
	}
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
		node->prev = tmp;
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
