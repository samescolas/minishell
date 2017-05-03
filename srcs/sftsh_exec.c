/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 19:49:51 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/02 15:52:37 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sftsh_exec.h"
#include "sftsh_types.h"
#include "sftsh_builtins.h"

static void	print_error_execve(char *str)
{
	write(1, "psh: no such file or directory: ", 32);
	ft_putendl(str);
}

int		exec_command(t_command *command)
{
	pid_t	child_pid;
	int		status;

	if (command->builtin_id >= 0)
		return (call_builtin(command));
	if (!command->path)
		print_error_execve(command->args[0]);
	child_pid = fork();
	if (child_pid < 0)
		return (1);
	if (child_pid == 0)
		execve(command->path, command->args, command->envp);
	else
		wait(&status);
	return (status);
}

int		sftsh_exec(t_command *commands)
{
	exec_command(commands);
	return (0);
}
