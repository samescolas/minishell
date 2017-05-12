/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 13:45:10 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/11 12:01:05 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "sftsh_types.h"
#include "../libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>

# define MAX_PATHLEN 512
# define BUFF_SIZE 32

# define DEFAULT_PROMPT "sftsh $>"
# define DEFAULT_COLOR "\x1B[90m"

# define DEF "\x1B[0m"
# define RED "\x1B[31m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CY1 "\x1B[36m"
# define CY2 "\x1B[37m"
# define CY3 "\x1B[96m"
# define BK2 "\x1B[90m"
# define BL2 "\x1B[94m"
# define MG2 "\x1B[95m"

volatile sig_atomic_t	g_ctrl_c_pressed;

#endif
