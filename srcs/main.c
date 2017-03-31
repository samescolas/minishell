/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:36:24 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static char	*prompt(char *p)
{
	char	*input;

	if (p)
		write(1, p, ft_strlen(p));
	else
		write(1, ">> ", 3);
	if (get_next_line(STDIN_FILENO, &input) <= 0)
		return (prompt(p));
	else
		return (input);
}

int		main(void)
{
	char	*command;
	char	*p;
	char	**args;

	p = (void *)0;
	while ((command = prompt(p)))
	{
		if (ft_strcmp(command, "exit") == 0)
			break ;
		if (ft_strncmp(command, "ps1=", 4) == 0)
			p = ft_strjoin(&(command[4]), " ");
		if (ft_strncmp(command, "echo", 4) == 0)
			ft_putendl(&(command[5]));
	}
	return (0);
}
