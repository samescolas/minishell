/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/12 16:20:34 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

static int	execute_command(t_command *command)
{
	if (builtin(command->path) >= 0)
		call_builtin(command);
	else
		exec_command(command);
}

int		start_shell(char **envp)
{
	char		*prompt_str;
	char		*prompt_color;
	char		*command_str;
	t_command	*command;

	prompt_str = (void *)0;
	prompt_color = (void *)0;
	command_str = (void *)0;
	command = (void *)0;
	while ((command_str = prompt(prompt_str, prompt_color)))
	{
		if (!(command = parse_command(command_str, envp)))
			continue ;
		if (builtin(command->path) >= 0)
			call_builtin(command);
		else
			exec_command(command);
		ft_strdel(&command_str);
		free_command(command);
	}
	ft_strdel(&prompt_str);
	ft_strdel(&prompt_color);
	return (0);
}

void	restore_env(char **envp)
{
	static char	**copy;
	int			i;

	i = 0;
	if (envp == (void *)0)
	{
		while (copy[i])
		{
			envp[i] = copy[i];
			++i;
		}
	}
	else
	{
		while (envp[i])
			++i;
		copy = (char **)malloc((i + 1) * sizeof(char *));
		i = 0;
		while (envp[i])
		{
			copy[i] = ft_strdup(envp[i]);
			++i;
		}
		copy[i] = (void *)0;	
	}
}

int		main(int argc, char **argv, char **envp)
{
	turn_off_ctrl_c();
	restore_env(envp);
	if (start_shell(envp) != 0)
		write(2, "something went wrong!\n", 22);
	restore_env((void *)0);
	return (0);
}
