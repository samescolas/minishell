/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_find_executable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:50:56 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/11 18:06:27 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "sftsh_env.h"

char		*check_path(char *path, char *cmd)
{
	char	*test_path;

	test_path = ft_strjoin(path, cmd);
	if (access(test_path, F_OK) == 0)
	{
		ft_strdel(&cmd);
		return (test_path);
	}
	ft_strdel(&test_path);
	return ((void *)0);
}

char		*check_current_directory(char *cmd)
{
	char	*test_path;
	char	*cwd;
	char	*tmp;

	cwd = getcwd((void *)0, MAX_PATHLEN);
	test_path = ft_strjoin(cwd, cmd);
	if (access(test_path, F_OK) == 0)
	{
		ft_strdel(&cwd);
		ft_strdel(&cmd);
		return (test_path);
	}
	ft_strdel(&cwd);
	ft_strdel(&test_path);
	return ((void *)0);
}

char		*check_command(char *command)
{
	if (access(command, F_OK) == 0)
		return (command);
	else
		return ((void *)0);
}

char		*find_executable_path(char *command, char **envp)
{
	char	**paths;
	char	*test_path;
	char	*cmd;
	int		i;

	if (check_command(command))
		return (command);
	cmd = ft_strjoin((command[0] == '/' ? "" : "/"), command);
	if (!get_env(envp, "PATH"))
		return ((void *)0);
	paths = ft_strsplit(get_env(envp, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		if ((test_path = check_path(paths[i++], cmd)))
		{
			ft_strarrdel(&paths);
			free(paths);
			return (test_path);
		}
	}
	ft_strarrdel(&paths);
	free(paths);
	if ((test_path = check_current_directory(cmd)))
		return (test_path);
	ft_strdel(&test_path);
	ft_strdel(&cmd);
	return ((void *)0);
}
