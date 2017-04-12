/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 13:45:10 by sescolas          #+#    #+#             */
/*   Updated: 2017/04/12 16:01:51 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			resize_buffer(char **line, unsigned int current_size)
{
	char	*tmp;

	tmp = ft_strnew(current_size + BUFF_SIZE);
	ft_strncpy(tmp, *line, current_size);
	ft_bzero(*line, current_size);
	free(*line);
	*line = tmp;
}

static void		bkspc(char *line, unsigned int *chars_copied)
{
	char	bkspc[3];

	if (*chars_copied == 0)
		return ;
	bkspc[0] = 8;
	bkspc[1] = 127;
	bkspc[2] = 8;
	line[--(*chars_copied)] = '\0';
	write(1, bkspc, 3);
}

static void		 display_char(char c, char *line, unsigned int *chars_copied)
{
	write(1, &c, 1);
	line[(*chars_copied)++] = c;
}

static void		handle_tab(char *line, unsigned int *chars_copied)
{
	if (*chars_copied == 0)
		ft_putendl("Would you really like all 127 things displayed?");
	else if (ft_strchr(line, ' '))
		autocomplete(line, chars_copied);
	else
		ft_putendl("List commands");
}

int				get_line(char **line)
{
	char			buf;
	int				ret;
	unsigned int	chars_copied;

	*line = ft_strdup("\0");
	chars_copied = 0;
	while ((ret = read(STDIN_FILENO, &buf, 1)) > 0)
	{
		if (chars_copied > 0 && chars_copied % BUFF_SIZE == 0)
			resize_buffer(line, chars_copied);
		if (ft_isprint(buf))
			display_char(buf, *line, &chars_copied);
		if (buf == 127)
				bkspc(*line, &chars_copied);
		else if (buf == '\t')
			handle_tab(*line, &chars_copied);
		else if (buf == 3)
		{
			write(1, "\n", 1);
			return (-1);
		}
		else if (buf == '\n' || buf == 10)
			break ;
	}
	write(1, "\n", 1);
	if (ret > 0 || **line != '\0')
		return (1);
	else 
		return (-1);
}
