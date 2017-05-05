/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:51:08 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/05 10:13:06 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "sftsh_expand.h"
#include "sftsh_exec.h"
#include "sftsh_find_x.h"
#include "sftsh_builtins.h"
#include "sftsh_types.h"
#include "sftsh_parse.h"
#include "sftsh_tokenize.h"

static int	count_args(char **tokens, int ix)
{
	int		num_items;

	num_items = ix;
	while (tokens[ix])
		++ix;
	return (ix - num_items);
}

static void	add_a_command(\
		t_command **list, char **tokens, char ***envp, int *ix)
{
	int			num_args;
	int			j;
	char		**args;
	char		action;
	t_command	*cmd;

	num_args = count_args(tokens, *ix);
	if (!(args = (char **)malloc((num_args + 1) * sizeof(char *))))
	{
		write(2, "memory error\n", 13);
		exit(0);
	}
	j = 0;
	while (tokens[*ix])
		args[j++] = ft_strdup(tokens[(*ix)++]);
	args[j] = (void *)0;
	add_command(list, create_command(args, envp, num_args));
}

t_command	*parse(char *command, char ***envp)
{
	t_command	*commands;
	t_command	*tmp;
	char		**tokens;
	int			i;

	tokens = tokenize(command);
	commands = (void *)0;
	expand_tokens(tokens, *envp);
	i = 0;
	while (tokens[i])
		add_a_command(&commands, tokens, envp, &i);
	return (commands);
}
