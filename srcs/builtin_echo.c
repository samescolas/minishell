/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:26:25 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/11 13:21:18 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sftsh_echo(t_command *command)
{
	int		no_newline;
	int		ix;

	if (command->num_args == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	ix = 1;
	if ((no_newline = (ft_strcmp(command->args[ix], "-n") == 0)))
		ix = 2;
	while (ix < command->num_args - 1)
		ft_padstr(command->args[ix++], 1, (void *)0);
	ft_padstr(command->args[ix], 0, (void *)0);
	if (!no_newline)
		write(1, "\n", 1);
	return (0);
}
