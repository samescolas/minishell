/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:57:44 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/05 09:44:10 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sftsh_read_line.h"
#include "sftsh_tokenize.h"
#include "sftsh_parse.h"
#include "sftsh_types.h"
#include "sftsh_exec.h"
#include "sftsh.h"

static char	*input(char *p, char *color)
{
	char	*input_str;

	ft_padstr((p ? p : ">>"), 1, color);
	if (read_line(&input_str) <= 0)
		return (input(p, color));
	else
		return (input_str);
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
	char		*prompt[3];
	t_command	*command;

	prompt[0] = (void *)0;
	prompt[1] = (void *)0;
	prompt[2] = (void *)0;
	while ((prompt[0] = input(prompt[1], prompt[2])))
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
