/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sftsh_tokenize.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:16:27 by sescolas          #+#    #+#             */
/*   Updated: 2017/05/15 12:54:25 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFTSH_TOKENIZE_H
# define SFTSH_TOKENIZE_H

# include <unistd.h>
# include <stdlib.h>

char	**tokenize(char *command);

#endif
