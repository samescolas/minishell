/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/11 17:10:17 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_args(char *str)
{
	if (ft_strchr(str, ' '))
		return (ft_strsplit(ft_strchr(str, ' ') + 1, ' '));
	else
		return ((void *)0);
}

int			ft_strcount(char *str, char c)
{
	if (!str || !*str)
		return (0);
	return ((*str == c) + ft_strcount(str + 1, c));
}

char		*expand_tilde(char *path, char **envp)
{
	char	*ret;
	char	*home;
	int		i;
	int		j;

	home = get_env(envp, "HOME");
	ret = ft_strnew((ft_strcount(path, '~') * (ft_strlen(home) - 1)) + ft_strlen(path));
	i = 0;
	j = 0;
	while (path[i])
	{
		if (path[i++] == '~')
		{
			ft_strcat(ret, home);
			j += ft_strlen(home);
		}
		else if (path[i - 1] == '/' && path[i] && path[i] == '~')
			continue ;
		else
			ret[j++] = path[i - 1];
	}
	return (ret);
}

char		*find_path(char *command, char **envp)
{
	char	**paths;
	char	*test_path;
	char	*cmd;

	if (command[0] == '/')
		cmd = ft_strdup(command);
	else
		cmd = ft_strjoin("/", command);
	paths = ft_strsplit(get_env(envp, "PATH"), ':');
	while (*paths)
	{
		test_path = ft_strjoin(*(paths++), cmd);
		if (access(test_path, X_OK) == 0)
		{
		   ft_strdel(&cmd);
		   return (test_path);
		}
		ft_strdel(&test_path);
	}
	ft_strdel(&cmd);
	return ((void *)0);
}

t_command	*parse_command(char *command, char **envp)
{
	t_command	*ret;
	t_tkn		*tokens;
	char		*tmp_path;

	tokens = get_tokens(command);
	if (!tokens)
		return ((void *)0);
	if (builtin(tokens->data) >= 0)
		ret = create_command(tokens->data, tokens->next, envp);
	else if ((tmp_path = find_path(tokens->data, envp)))
		ret = create_command(tmp_path, tokens, envp);
	else
	{
		write(2, "sftsh: command not found: ", 26);
		write(2, tokens->data, tokens->size);
		write(2, "\n", 1);
		return ((void *)0);
	}
	return (ret);
}
