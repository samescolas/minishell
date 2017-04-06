/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/06 13:39:33 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

int		is_valid_command(char *command)
{
	if (ft_strcount(command, '\'') % 2 || ft_strcount(command, '"') % 2)
		return (0);
	return (1);
}

static t_tkn	*tokenize_command(char *command)
{ 
	t_tkn	*ret;
	int		i;

	ret = (void *)0;
	i = 0;
	while (command[i] && command[i] == ' ')
		++i;
	while (command[i])
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			append_list(&ret, create_list_item(\
				&(command[i + 1]), ft_strfind(&(command[i + 1]), command[i])));
			i += ft_strfind(&(command[i + 1]), command[i]) + 2;
		}
		else
		{
			append_list(&ret, create_list_item(\
				&(command[i]), ft_strfind(&(command[i]), ' ')));
			i += ft_strfind(&(command[i]), ' ');
		}
		while (command[i] && command[i] == ' ')
			++i;
	}
	return (ret);
}

static void	print_error_message(void)
{
	write(2, "invalid brackets found\n", 23);
	exit(0);
}

t_tkn		*get_tokens(char *command)
{
	t_tkn	*ret;
	t_tkn	*tmp;

	ret = (void *)0;
	if (!command || !*command)
		return (ret);
	if ((ret = tokenize_command(command)))
	{
		tmp = ret;
		while (tmp)
		{
			if (!valid_bracket((char *)(tmp->data)))
				print_error_message();
			tmp = tmp->next;
		}
	}
	return (ret);
}
