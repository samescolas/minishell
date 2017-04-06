/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/06 14:25:57 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

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
		if (ft_strlen(command_str) == 1 && command_str[0] == 3)
			continue ;
		command = parse_command(command_str, envp);
		if (!command)
			continue ;
		if (builtin(command->path) >= 0)
			call_builtin(command);
		else
			call_func(command->path, command->env);
		ft_strdel(&command_str);
		free_command(command);
	}
	ft_strdel(&prompt_str);
	ft_strdel(&prompt_color);
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	turn_off_ctrl_c();
	if (start_shell(envp) != 0)
		write(2, "something went wrong!\n", 22);
	return (0);
}
