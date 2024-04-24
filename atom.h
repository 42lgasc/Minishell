/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:07:26 by lgasc             #+#    #+#             */
/*   Updated: 2024/04/24 15:29:58 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOM_H
# define ATOM_H

///`plain_text` shall contain no `Blank`.
///`double_quote` may contain `NamedVariable`s.
enum e_atom
{
	Blank,
	PlainText,
	SingleQuote,
	DoubleQuote,
	InputRedirection,
	OutputRedirection,
	HereDocument,
	AppendingRedirection,
	Pipe,
	NamedParameter,
	StatusParameter,
};
	//
typedef struct s_atom
{
	const enum e_atom	type;
	union
	{
		char *const	plain_text;
		char *const	single_quote;
		char *const	double_quote;
		char *const	named_parameter;
	};
}	t_atom;
#endif
