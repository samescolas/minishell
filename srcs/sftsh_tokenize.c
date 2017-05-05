/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:19:21 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/05 11:03:51 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sftsh_types.h"
#include "sftsh_brackets.h"
#include "sftsh_tokenize.h"

static void		print_error_message(void)
{
	write(2, "invalid brackets found\n", 23);
	exit(0);
}

static int		count_tokens(char *command)
{
	int		num_tokens;
	int		i;
	int		offset;

	num_tokens = 0;
	i = 0;
	while (command[i] && command[i] == ' ')
		++i;
	while (command[i])
	{
		if (command[i] == '"' || command[i] == '\'')
			i += ft_strfind(&(command[i + 1]), command[i]) + 2;
		else
			i += ft_strfind(&(command[i]), ' ');
		if (command[i - 2] && command[i - 1] == ';' && command[i - 2] != ' ')
			++num_tokens;
		while (command[i] && command[i] == ' ')
			++i;
		++num_tokens;
	}
	return (num_tokens);
}

static void		add_string(char **list, char *str, size_t size, int *ix)
{
	int		semicolon;
	char	*ret;

	ret = (void *)0;
	semicolon = (str[size - 1] == ';' && size > 1);
	if ((ret = ft_strnew(size)))
		ft_strncpy(ret, str, size);
	list[(*ix)++] = ret;
	if (semicolon)
	{
		ret[size - 1] = '\0';
		list[(*ix)++] = ft_strdup(";");
	}
	if (!str[size])
		list[(*ix)] = (void *)0;
}

static void		add_token(char **list, char *command, int *ix)
{
	if (command[ix[0]] == '"' || command[ix[0]] == '\'')
	{
		add_string(list, &(command[ix[0] + 1]),\
			ft_strfind(&(command[ix[0] + 1]), command[ix[0]]), &ix[1]);
		ix[0] += ft_strfind(&(command[ix[0] + 1]), command[ix[0]]) + 2;
	}
	else
	{
		add_string(list, &command[ix[0]],\
				ft_strfind(&command[ix[0]], ' '), &ix[1]);
		ix[0] += ft_strfind(&(command[ix[0]]), ' ');
	}
	while (command[ix[0]] && command[ix[0]] == ' ')
		++ix[0];
}

char			**tokenize(char *command)
{
	char	**ret;
	int		ix[2];

	if (!(ret = (char **)malloc((count_tokens(command) + 1) * sizeof(char *))))
		return ((void *)ret);
	ix[0] = 0;
	ix[1] = 0;
	while (command[ix[0]] && command[ix[0]] == ' ')
		++(ix[0]);
	while (command[ix[0]])
		add_token(ret, command, (int *)ix);
	return (ret);
}
