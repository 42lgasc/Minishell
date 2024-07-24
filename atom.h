/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:07:26 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 20:59:58 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOM_H
# define ATOM_H

# include "here_document.h"
# include "particle.h"
# include "miscellaneous.h"

enum e_atom
{
	Atom_Field,
	Atom_Input,
	Atom_Output,
	Atom_HereDocument,
	Atom_Appending,
	Atom_Pipe,
};
// A collation of `plain_text`, `single_quote`, `double_quote`, and `variable`:
//const t_word_splitable	s_atom::<union>::string;
///`plain_text` shall contain no `Blank`.
///`single_quote` shall be `NULL` when it has no length.
///	XXX: Should a `&'\0'` empty string be used instead?	~~lgasc 2024-06-13 21:42
///Only the `here_document.word` is part of the command;
///	The actual document is not -- it is input afterward.
///According to the Bash manual, section 3.4 Parameters,
///>A _variable_ is a parameter denoted by a `name`.
///`variable` shall exclude the leading `$` parameter sign.
///	Enclosing a parameter in braces is not on support
///		for the scope of this "minishell" project.
///`Blank`, `Pipe`, and `StatusParameter` have no visible
///	value in the `union` as they are unitary markers.
typedef struct s_atom
{
	enum e_atom	type;
	union
	{
		t_particle_node	field;
		t_particle_node	input;
		t_particle_node	output;
		t_particle_node	appending;
		t_here_document	here_document;
	};
}				t_atom;
t_atom	ft_atom(const char *s)
		__attribute__	((nonnull,	warn_unused_result));
void	ft_free_atom(t_atom a);
#endif
