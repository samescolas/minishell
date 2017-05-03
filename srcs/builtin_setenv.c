/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:31:04 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/02 21:29:34 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sftsh_env.h"

int		sftsh_setenv(t_command *command)
{
	char	*tmp;

	if (command->num_args > 2)
	{
		if ((tmp = get_env(command->envp, command->args[0])))
		{
			set_env(command->envp, command->args[0], command->args[1]);
			ft_strdel(&tmp);
		}
		else
			append_env(&command->envp, command->args[0], command->args[1]);
	}
	else
		while (*(command->envp))
			ft_putendl(*(command->envp++));
	return (0);
}
