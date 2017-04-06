/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/06 13:49:47 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_args(char *str)
{
	if (ft_strchr(str, ' '))
		return (ft_strsplit(ft_strchr(str, ' ') + 1, ' '));
	else
		return ((void *)0);
}

int		ft_strcount(char *str, char c)
{
	if (!str || !*str)
		return (0);
	return ((*str == c) + ft_strcount(str + 1, c));
}

char	*get_env(char **envp, char *val)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(val);
	while (envp[i])
		if (ft_strncmp(envp[i++], val, len) == 0)
			return (&(envp[i - 1][len + 1]));
	return ((void *)0);
}

char	*expand_tilde(char *path, char **envp)
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

	tokens = get_tokens(command);
	if (!tokens)
		return ((void *)0);
	if (builtin((char *)(tokens->data)) >= 0)
		ret = create_command((char *)(tokens->data), tokens->next, envp);
	else
		ret = create_command(find_path(tokens->data, envp), tokens->next, envp);
	return (ret);
}
