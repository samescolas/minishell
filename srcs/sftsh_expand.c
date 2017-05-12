/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:43:12 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/11 18:59:11 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "sftsh_env.h"
#include "sftsh_expand.h"
#include "minishell.h"

char		*expand_tilde(char *path, char **envp)
{
	char	*ret;
	char	*home;
	int		ix[2];
	int		len;

	if (ft_strchr(path, '~') == (void *)0)
		return (path);
	home = get_env(envp, "HOME");
	len = ft_strlen(home);
	ret = ft_strnew((ft_strcount(path, '~') * (len - 1)) + ft_strlen(path));
	ix[0] = -1;
	ix[1] = 0;
	while (path[++(ix[0])])
	{
		if (path[ix[0]] == '~')
		{
			ft_strcat(ret, home);
			ft_strcat(ret, "/");
			ix[1] += len + 1;
		}
		else
			ret[(ix[1])++] = path[ix[0]];
	}
	ft_strdel(&path);
	return (ret);
}

char		*replace_var(char *orig_str, char *var, int var_len, char **envp)
{
	char	*val;
	char	*ret;
	int		i;
	int		j;

	val = get_env(envp, var);
	if (!(ret = ft_strnew(ft_strlen(val) + ft_strlen(orig_str) - var_len)))
		return (orig_str);
	i = 0;
	j = 0;
	while (orig_str[i] && orig_str[i] != '$')
		ret[j++] = orig_str[i++];
	if (val)
		ft_strcat(ret, val);
	j += ft_strlen(val);
	++i;
	while (orig_str[i] && orig_str[i] != ' ')
		++i;
	while (orig_str[i])
		ret[j++] = orig_str[i++];
	ft_strdel(&orig_str);
	return (ret);
}

char		*expand_vars(char *str, char **envp)
{
	int		var_len;
	char	*var_start;
	char	*var;

	var_start = str - 1;
	while ((var_start = ft_strchr(var_start + 1, '$')))
	{
		var_len = -1;
		while (var_start[++var_len])
			if (var_start[var_len] == ' ')
				break ;
		if (!var_start[1])
			break ;
		var = ft_strsub(var_start, 1, var_len - 1);
		str = replace_var(str, var, var_len - 1, envp);
	}
	return (str);
}

char		*expand_dots(char *str, char **envp)
{
	char	*ret;
	char	*tmp;

	if (*str && *str != '.')
		return (str);
	if (ft_strcmp(str, ".") == 0)
	{
		ret = getcwd((void *)0, MAX_PATHLEN);
		ft_strdel(&str);
		return (ret);
	}
	else if (ft_strcmp(str, "..") == 0)
	{
		ret = getcwd((void *)0, MAX_PATHLEN);
		ft_strdel(&str);
		tmp = ft_strrchr(ret, '/');
		*tmp = '\0';
		return (ret);
	}
	else
		return (str);
}

void		expand_tokens(char **tokens, char **envp)
{
	char	**tmp;

	tmp = tokens;
	while (*tmp)
	{
		*tmp = expand_tilde(*tmp, envp);
		*tmp = expand_vars(*tmp, envp);
		*tmp = expand_dots(*tmp, envp);
		++tmp;
	}
}
