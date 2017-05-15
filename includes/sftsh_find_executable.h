/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_find_executable.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 12:43:07 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/15 12:50:17 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFTSH_FIND_EXECUTABLE_H
# define SFTSH_FIND_EXECUTABLE_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>

char	*find_executable_path(char *command, char **envp);

#endif
