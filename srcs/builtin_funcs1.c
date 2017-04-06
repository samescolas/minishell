/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 10:08:43 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/06 14:51:36 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

int		sftsh_echo(t_command *command)
{
	t_tkn	*tmp;

	if (!(command->args))
	{
		write(1, "\n", 1);
		return (0);
	}
	tmp = command->args;
	while (tmp)
	{
		/* it would be cool for this to be in color if something existed in command->env */
		ft_padstr((char *)(tmp->data), 1, (void *)0);
		tmp = tmp->next;
	}
	return (0);
}

int		sftsh_cd(t_command *command)
{
	char	*full_path;

	if (command->args == (void *)0)
		full_path = expand_tilde("~", command->env);
	else
		full_path = expand_tilde(command->args->data, command->env);
	if (command->args && command->args->next != NULL)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (access(full_path, R_OK) == 0)
	{
		chdir(full_path);
		ft_strdel(&full_path);
		return (0);
	}
	write(2, "cd: no such file or directory: ", 31);
	write(2, command->args->data, command->args->size);
	write(2, "\n", 1);
	return (1);
}

static void	print_help(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		ft_putendl("there's no such thing as a stupid question");
}

int		sftsh_exit(t_command *command)
{
	if (command->args != NULL && ft_strcmp(command->args->data, "help") == 0)
		print_help("exit");
	/* free_command(&command); */
	exit(0);
}

int		sftsh_env(t_command *command)
{
	char	**envp;

	if (command->args != NULL)
	{
		write(2, "env: no such file or directory\n", 31);
		return (1);
	}
	envp = command->env;
	while (*envp)
		ft_putendl(*(envp++));
	return (0);
}
