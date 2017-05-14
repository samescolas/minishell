/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:57:44 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/13 21:05:46 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sftsh_read_line.h"
#include "sftsh_parse.h"
#include "sftsh_types.h"
#include "sftsh_exec.h"
#include "sftsh.h"

static char	*input(char *prompt[3])
{
	char		*input_text;
	int			line_read;

	ft_strdel(&prompt[0]);
	ft_padstr((prompt[1] ? prompt[1] : DEFAULT_PROMPT)\
			, 1, (prompt[2] ? prompt[2] : DEFAULT_COLOR));
	line_read = read_line(&input_text);
	while (line_read <= 0 && !g_ctrl_c_pressed)
	{
		ft_strdel(&input_text);
		ft_padstr((prompt[1] ? prompt[1] : DEFAULT_PROMPT)\
			, 1, (prompt[2] ? prompt[2] : DEFAULT_COLOR));
		line_read = read_line(&input_text);
	}
	return (input_text);
}

static char	*get_color(char *color)
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

static int	delete_prompt(char *prompt[3])
{
	ft_strdel(&prompt[0]);
	ft_strdel(&prompt[1]);
	ft_strdel(&prompt[2]);
	return (0);
}

int			sftsh(char ***envp)
{
	t_command	*command;
	char		*prompt[3];

	prompt[0] = (void *)0;
	prompt[1] = (void *)0;
	prompt[2] = (void *)0;
	while ((prompt[0] = input(prompt)))
	{
		if (ft_strncmp(prompt[0], "ps1=", 4) == 0)
		{
			ft_strdel(&prompt[1]);
			prompt[1] = ft_strdup(&prompt[0][4]);
		}
		else if (ft_strncmp(prompt[0], "col=", 4) == 0)
		{
			ft_strdel(&prompt[2]);
			prompt[2] = get_color(ft_strmap(&prompt[0][4], &ft_tolower));
		}
		else if ((command = parse(prompt[0], envp)))
		{
			if (sftsh_exec(command) == -42)
				break ;
		}
	}
	return (delete_prompt(prompt));
}
