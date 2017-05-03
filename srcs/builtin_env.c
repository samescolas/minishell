/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:18:39 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/03 11:40:55 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sftsh_env.h"
#include "minishell.h"

static void	set_env_val(char ***envp, char *str)
{
	char	*variable;
	int		len;

	ft_putendl("inside set_env_val");
	len = ft_strfind(str, '=') - 1;
	variable = ft_strsub(str, 0, len + 1);
	if (get_env(*envp, variable) != (void *)0)
		set_env(*envp, variable, &str[len + 2]);
	else
		append_env(envp, variable, &str[len + 2]);
}

int		sftsh_env(t_command *command)
{
	char **envp;

	envp = command->envp;
	if (command->num_args > 1)
	{
		if ((char)*((command->args)[1]) == '-')
			return (0);
		else
			if (ft_strchr(command->args[1], '='))
				set_env_val(&envp, command->args[1]);
	}
	while (*envp)
		ft_putendl(*(envp++));
	return (0);
}
