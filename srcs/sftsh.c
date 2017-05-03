/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:57:44 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/03 11:26:27 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

char	*get_color(char *color)
{
	if (ft_strcmp(color, "default") == 0 || ft_strcmp(color, "def") == 0)
		return (ft_strdup(DEF));
	else if (ft_strcmp(color, "red") == 0 || ft_strcmp(color, "r") == 0)
		return (ft_strdup(RED));
	else if (ft_strcmp(color, "blue") == 0 || ft_strcmp(color, "b") == 0)
		return (ft_strdup(BLU));
	else if (ft_strcmp(color, "magenta") == 0 || ft_strcmp(color, "m") == 0)
		return (ft_strdup(MAG));
	else if (ft_strcmp(color, "c2") == 0)
		return (ft_strdup(CY2));
	else if (ft_strcmp(color, "c3") == 0)
		return (ft_strdup(CY3));
	else if (ft_strcmp(color, "bk2") == 0)
		return (ft_strdup(BK2));
	else if (ft_strcmp(color, "bl2") == 0)
		return (ft_strdup(BL2));
	else if (ft_strcmp(color, "m2") == 0)
		return (ft_strdup(MG2));
	else
		return ((void *)0);
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
	{
		if (ft_strncmp(command_str, "ps1=", 4) == 0)
			prompt_str = ft_strdup(&command_str[4]);
		else if (ft_strncmp(command_str, "col=", 4) == 0)
			prompt_color = get_color(&command_str[4]);
		else if ((command = parse(tokenize(command_str), envp)))
			sftsh_exec(command);
	}
	ft_strdel(&prompt_str);
	ft_strdel(&prompt_color);
	return (0);
}
