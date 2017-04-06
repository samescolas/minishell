/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/06 13:50:29 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

int		call_func(char *command, char *envp[])
{
	pid_t	child_pid;
	char	**args;
	int		stat;

	if (!command || ft_strlen(command) == 0)
		return (0);
	args = ft_strsplit(command, ' ');
	if (access(command, X_OK) == 0)
		child_pid = fork();
	else
	{
		write(1, "psh: no such file or directory: ", 32);
		ft_putendl(args[0]);
	}
	if (child_pid >= 0)
	{
		if (child_pid == 0)
			execve(command, args, envp);
		else
		{
			wait(&stat);
			return (1);
		}
	}
	else
		return (0);
	return (1);
}
