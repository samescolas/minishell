/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/11 18:15:19 by sescolas         ###   ########.fr       */
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
	{
		if (ft_strncmp(envp[i], val, len) == 0 && envp[i][len] == '=')
			return (&(envp[i][len + 1]));
	}
	return ((void *)0);
}

void	append_env(char ***envp, char *str)
{
	int		i;
	int		len;
	char	*tmp;
	char	**ret;

	ret = (void *)0;
	len = ft_strfind(str, '=') - 1;
	i = 0;
	while ((*envp)[i])
		++i;
	if (!(ret = (char **)malloc((i + 2) * sizeof(char *))))
		return ;
	i = -1;
	while ((*envp)[++i])
		ret[i] = (*envp)[i];
	ret[i++] = str;
	ret[i] = (void *)0;
	*envp = ret;
}

void	set_env(char **envp, char *var, char *value)
{
	int		i;
	int		len;
	char	*ret;

	len = ft_strlen(var);
	ret = ft_strnew(len + ft_strlen(value) + 1);
	ft_strcpy(ret, var);
	ft_strcat(ret, "=");
	ft_strcat(ret, value);
	i = -1;
	while (envp[++i])
		if (ft_strncmp(var, envp[i], len) == 0 && envp[i][len] == '=')
			break ;
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
			ret[len] = envp[len];
		ret[len] = (void *)0;
	}
	return (ret);
}
