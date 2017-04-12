/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/12 16:12:39 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

t_command	*create_command(char *path, t_tkn *args, char **envp)
{
	t_command	*ret;

	if ((ret = (t_command *)malloc(sizeof(t_command))))
	{
		ret->path = ft_strdup(path);
		ret->args = args;
		ret->env = envp;
		ret->builtin = 0;
		ret->next = NULL;
	}
	return (ret);
}

void	push_command(t_command **stack, t_command *command)
{
	if (!stack || !*stack)
		*stack = command;
	else
	{
		command->next = (*stack)->next;
		*stack = command;
	}
}

t_command	*pop_command(t_command **stack)
{
	t_command	*ret;

	if (!stack || !*stack)
		return ((void *)0);
	ret = (void *)0;
	ret = *stack;
	*stack = (*stack)->next;
	return (ret);
}

void	free_command(t_command *command)
{
	ft_strdel(&(command->path));
	command->path = (void *)0;
	command->args = (void *)0;
	command->next = (void *)0;
}

void	free_commands(t_command **stack)
{
	t_command	*tmp;

	while ((tmp = pop_command(stack)))
		free_command(tmp);
	*stack = (void *)0;
}
