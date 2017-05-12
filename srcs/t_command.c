/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/11 18:08:16 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "sftsh_builtins.h"
#include "sftsh_types.h"

t_command	*create_command(char **args, char ***envp, int num_args)
{
	t_command	*ret;

	if ((ret = (t_command *)malloc(sizeof(t_command))))
	{
		if ((ret->builtin_id = find_builtin(args[0])) < 0)
			ret->path = find_executable_path(args[0], *envp);
		else
			ret->path = (void *)0;
		ret->num_args = num_args;
		ret->args = args;
		ret->envp = envp;
		ret->next = (void *)0;
	}
	return (ret);
}

void		add_command(t_command **queue, t_command *command)
{
	t_command	*tmp;

	if (!queue)
		return ;
	if (!*queue)
		*queue = command;
	else
	{
		tmp = *queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = command;
	}
}

t_command	*pop_command(t_command **stack)
{
	t_command	*ret;

	if (!stack || !*stack)
		return ((void *)0);
	if (!(*stack)->next)
	{
		ret = *stack;
		*stack = (void *)0;
		return (ret);
	}
	ret = (void *)0;
	ret = *stack;
	*stack = (*stack)->next;
	return (ret);
}

void		free_command(t_command *command)
{
	ft_strarrdel(&(command->args));
	ft_strdel(&(command->path));
	free(command->args);
	command->path = (void *)0;
	command->args = (void *)0;
	command->next = (void *)0;
	command->num_args = 0;
	free(command);
}

void		free_commands(t_command **stack)
{
	t_command	*tmp;

	while ((tmp = pop_command(stack)))
		free_command(tmp);
	*stack = (void *)0;
}
