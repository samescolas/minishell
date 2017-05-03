/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:20:33 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/02 21:41:44 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sftsh_types.h"
#include "sftsh_expand.h"
#include "sftsh_env.h"

int		sftsh_cd(t_command *command)
{
	char	*full_path;

	if (command->num_args > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (command->num_args == 0)
		full_path = expand_tilde("~", command->envp);
	else if (ft_strcmp((command->args)[1], "-") == 0)
		full_path = ft_strdup(get_env(command->envp, "OLDPWD"));
	else
		full_path = expand_tilde((command->args)[1], command->envp);
	ft_putendl("still here");
	if (access(full_path, R_OK) == 0)
	{
		set_env(command->envp, "OLDPWD", getcwd((void *)0, MAX_PATHLEN));
		chdir(full_path);
		//ft_strdel(&full_path);
		return (0);
	}
	write(2, "cd: no such file or directory: ", 31);
	write(2, (command->args)[1], ft_strlen((command->args)[1]));
	write(2, "\n", 1);
	return (1);
}
