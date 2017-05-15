/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 19:49:51 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/14 19:38:14 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sftsh_exec.h"
#include "sftsh_types.h"
#include "sftsh_builtins.h"
#include "minishell.h"

static void	ctrl_c_handler(int sig)
{
	signal(sig, ctrl_c_handler);
}

int			exec_command(t_command *command)
{
	pid_t	child_pid;
	int		status;
	void	*prev_handler;

	prev_handler = signal(SIGINT, ctrl_c_handler);
	if (command->builtin_id >= 0)
		return (call_builtin(command));
	if (command->path == (void *)0)
		return (1);
	if ((child_pid = fork()) < 0)
		return (1);
	if (child_pid == 0)
		execve(command->path, command->args, *command->envp);
	else
		waitpid(child_pid, &status, 0);
	signal(SIGINT, prev_handler);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}

void		inquire(char *command)
{
	ft_putstr("what the shell");
	if (command)
	{
		ft_putstr(" is ");
		ft_putstr(command);
	}
	ft_putendl("?");
}

int			sftsh_exec(t_command *commands)
{
	t_command	*cmd;
	int			status;

	status = 0;
	while ((cmd = pop_command(&commands)) && status == 0)
	{
		if (cmd->path && access(cmd->path, X_OK) != 0)
		{
			ft_putstr("you cant use that: ");
			ft_putendl(cmd->path);
		}
		if (cmd->builtin_id >= 0 || cmd->path)
			status = exec_command(cmd);
		else
			inquire(cmd->args[0]);
		free_command(cmd);
	}
	commands = (void *)0;
	return (status);
}
