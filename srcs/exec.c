/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/11 15:40:59 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

static char	**list_to_arr(t_tkn *arg_list)
{
	t_tkn	*tmp;
	char	**ret;
	int		i;

	i = 0;
	tmp = arg_list;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	ret = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while(arg_list)
	{
		ret[i++] = ft_strdup(arg_list->data);
		arg_list = arg_list->next;
	}
	ret[i] = (void *)0;
	return (ret);
}

static void	print_error_execve(char *str)
{
	write(1, "psh: no such file or directory: ", 32);
	ft_putendl(str);
}

int		exec_command(t_command *command)
{
	pid_t	child_pid;
	char	**args;
	int		status;

	if (!command)
		return (1);
	if (!command->path)
		print_error_execve(command->args->data);
	args = list_to_arr(command->args);
	child_pid = fork();
	if (child_pid < 0)
		return (1);
	if (child_pid == 0)
		execve(command->path, args, command->env);
	else
		wait(&status);
	return (status);
}
