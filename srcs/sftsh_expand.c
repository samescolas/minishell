/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:43:12 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/05 18:22:02 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "sftsh_env.h"
#include "sftsh_expand.h"

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
	if (!val)
		return (orig_str);
	ret = ft_strnew(ft_strlen(val) + ft_strlen(orig_str) - var_len);
	i = 0;
	j = 0;
	while (orig_str[i] && orig_str[i] != '$')
		ret[j++] = orig_str[i++];
	ft_strcat(ret, val);
	j += ft_strlen(val);
	++i;
	while (orig_str[i] && orig_str[i] != ' ')
		++i;
	while (orig_str[i])
		ret[j++] = orig_str[i++];
	return (ret);
}

char		*expand_vars(char *str, char **envp)
{
	int		var_len;
	char	*var_ind;
	char	*var;

	var_ind = str - 1;
	while ((var_ind = ft_strchr(var_ind + 1, '$')))
	{
		var_len = -1;
		while (var_ind[++var_len])
			if (var_ind[var_len] == ' ')
				break ;
		if (!var_ind[1])
			break ;
		var = ft_strsub(var_ind, 1, var_len - 1);
		str = replace_var(str, var, var_len - 1, envp);
	}
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
		++tmp;
	}
}
