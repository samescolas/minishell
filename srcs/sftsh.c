/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:57:44 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/02 15:48:49 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sftsh_read_line.h"
#include "sftsh_tokenize.h"
#include "sftsh_parse.h"
#include "sftsh_types.h"
#include "sftsh_exec.h"
#include "sftsh.h"

static char	*prompt(char *p, char *color)
{
	char	*input;

	ft_padstr((p ? p : ">>"), 1, color);
	if (read_line(&input) <= 0)
		return (prompt(p, color));
	else
		return (input);
}

void	display_command(t_command command)
{
	if (command.builtin_id >= 0)
		ft_putstr(command.args[0]);
	else
		ft_putstr(command.path);
	for (int i=1; i < command.num_args; i++)
	{
		ft_putstr(" ");
		ft_putstr(command.args[i]);
	}
	ft_putendl("");
}

int		sftsh(char **envp)
{
	char		*prompt_str;
	char		*prompt_color;
	char		*command_str;
	t_command	*command;
	char		**tokens;

	prompt_str = (void *)0;
	prompt_color = (void *)0;
	command_str = (void *)0;
	command = (void *)0;
	while ((command_str = prompt(prompt_str, prompt_color)))
		if ((command = parse(tokenize(command_str), envp)))
			sftsh_exec(command);
	ft_strdel(&prompt_str);
	ft_strdel(&prompt_color);
	return (0);
}
