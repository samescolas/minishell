/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:19:21 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/12 16:11:31 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sftsh_types.h"
#include "sftsh_brackets.h"
#include "sftsh_tokenize.h"

static void		print_error_message(void)
{
	write(2, "invalid brackets found\n", 23);
	//exit(0);
}

int			count_tokens(char *command)
{
	int		num_tokens;
	char	*ptr;

	ptr = command;
	while (*ptr && (*ptr == ' ' || *ptr == ';'))
		++ptr;
	num_tokens = 0;
	while (*ptr)
	{
		if (*ptr == '"' || *ptr == '\'')
		{
			++num_tokens;
			if (!ft_strchr(ptr + 1, *ptr))
			{
				print_error_message();
				return (0);
			}
			else
				ptr = ft_strchr(ptr + 1, *ptr) + 1;
		}
		else if (*ptr == ';')
		{
			++num_tokens;
			++ptr;
		}
		else
		{
			while (*ptr && *ptr != ' ' && *ptr != ';' && *ptr != '"' && *ptr != '\'')
				++ptr;
			++num_tokens;
		}
		while (*ptr && *ptr == ' ')
			++ptr;
	}
	return (num_tokens);
}

char	*add_string(char *start, char delim)
{
	int		i;
	char	*ret;

	i = 0;
	if (delim == '\0')
	{
		if (!ft_strchr(start, ';') && !ft_strchr(start, ' '))
			return (ft_strdup(start));
		while (start[i] && start[i] != ' ' && start[i] != ';')
			++i;
		ret = ft_strsub(start, 0, i);
	}
	else
	{
		if (!(ret = ft_strnew(ft_strfind(start, delim))))
			return ((void *)0);
		while (start[i] && start[i] != delim)
		{
			ret[i] = start[i];
			++i;
		}
		ret[i] = '\0';
	}
	return (ret);
}

char	**tokenize(char *command)
{
	char	**ret;
	char	*ptr;
	int		i;

	if (!(i = count_tokens(command)))
		return ((void *)0);
	if (!(ret = (char **)malloc((i + 1) * sizeof(char *))))
		return ((void *)0);
	ptr = command;
	while (*ptr && (*ptr == ' ' || *ptr == ';'))
		++ptr;
	i = 0;
	while (*ptr)
	{
		if (*ptr == '"' || *ptr == '\'')
		{
			ret[i++] = add_string(ptr + 1, *ptr);
			ptr = ft_strchr(ptr + 1, *ptr) + 1;
		}
		else if (*ptr == ';')
		{
			ret[i++] = ft_strdup(";");
			++ptr;
		}
		else
		{
			ret[i++] = add_string(ptr, '\0');
			while (*ptr && *ptr != ' ' && *ptr != ';')
				++ptr;
		}
		while (*ptr && *ptr == ' ')
			++ptr;
	}
	ret[i] = (void *)0;
	return (ret);
}
