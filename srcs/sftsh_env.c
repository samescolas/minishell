/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:36:34 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/03 12:36:20 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **envp, char *val)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(val);
	while (envp[++i])
		if (ft_strncmp(envp[i], val, len) == 0 && envp[i][len] == '=')
			return (&(envp[i][len + 1]));
	return ((void *)0);
}

void	append_env(char ***envp, char *var, char *val)
{
	char	**ret;
	int		i;

	i = 0;
	while ((*envp)[i])
		++i;
	if (!(ret = (char **)malloc((i + 2) * sizeof(char *))))
		return ;
	i = -1;
	while ((*envp)[++i])
		ret[i] = (*envp)[i];
	ret[i] = ft_strnew(ft_strlen(var) + ft_strlen(val) + 1);
	ft_strcpy(ret[i], var);
	ft_strncat(ret[i], "=", 1);
	ft_strcat(ret[i++], val);
	ret[i] = (void *)0;
	*envp = ret;
}

void	set_env(char **envp, char *var, char *value)
{
	int		i;
	int		len;
	char	*ret;
	char	*tmp;

	len = ft_strlen(var);
	ret = ft_strnew(len + ft_strlen(value) + 1);
	ft_strcpy(ret, var);
	ft_strcat(ret, "=");
	ft_strcat(ret, value);
	i = -1;
	while (envp[++i])
		if (ft_strncmp(var, envp[i], len) == 0 && envp[i][len] == '=')
			break ;
	tmp = envp[i];
	envp[i] = ret;
}

char		**copy_env(char **envp)
{
	char	**ret;
	int		len;

	len = 0;
	while (envp[len])
		++len;
	if ((ret = (char **)malloc((len + 1) * sizeof(char *))))
	{
		len = -1;
		while (envp[++len])
			ret[len] = ft_strdup(envp[len]);
		ret[len] = (void *)0;
	}
	return (ret);
}

void		restore_env(char **env, char **copy)
{
	int		i;

	i = -1;
	while (env[++i])
		env[i] = copy[i];
}
