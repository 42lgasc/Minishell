/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:21:34 by lgasc             #+#    #+#             */
/*   Updated: 2024/04/24 20:05:41 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef int	t_pipefd;

///It is valid for the `command_word` to be `NULL`,
///	as long as an input or output redirection is specified.
///The `arguments` shall not be if the `command_word` is `NULL`.
typedef struct s_command
{
	const t_pipefd	input;
	const t_pipefd	output;
	char *const		command_word;
	union
	{
		char (*const	arguments)[];
	};
}	t_command;
#endif
