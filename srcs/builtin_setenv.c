/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:31:04 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/03 11:54:41 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sftsh_env.h"

int		sftsh_setenv(t_command *command)
{
	char	*tmp;
	int		num_items;
	int		i;

	i = 1;
	num_items = (command->num_args - 1) / 2;
	while (num_items--)
	{
		if ((tmp = get_env(command->envp, command->args[i])))
			set_env(command->envp, command->args[i], command->args[i + 1]);
		else
			append_env(&command->envp, command->args[i], command->args[i + 1]);
		i += 2;
	}
	if (command->num_args == 1)
		while (*(command->envp))
			ft_putendl(*(command->envp++));
	return (0);
}
