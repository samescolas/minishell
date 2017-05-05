/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 19:49:51 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/04 13:50:39 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sftsh_exec.h"
#include "sftsh_types.h"
#include "sftsh_builtins.h"

static void	print_error_execve(char *str)
{
	write(1, "psh: command not found: ", 24);
	ft_putendl(str);
}

int		exec_command(t_command *command)
{
	pid_t	child_pid;
	int		status;

	if (command->builtin_id >= 0)
		return (call_builtin(command));
	if ((child_pid = fork()) < 0)
		return (1);
	if (child_pid == 0)
		execve(command->path, command->args, *command->envp);
	else
		waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}

int		sftsh_exec(t_command *commands)
{
	return (exec_command(commands));
}
