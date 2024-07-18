/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:07:26 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/18 05:50:58 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  ATOM_H
# define ATOM_H

# include <stdbool.h>

# include "quark.h"

typedef bool				t_fail	__attribute__	((deprecated));
//# define OK		false
//# define ERROR	true

///A BLank, as the `bash` manual states.
# define BLANK			" \t"
# define DIGIT			"0123456789"
# define CAPITAL			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define SMALL			"abcdefghijklmnopqrstuvwxyz"
# define NO_PLAIN		"\"$'"
///A Metacharacter, as the `bash` manual states.
///XXX: There is yet a requirement to not support some of such characters.
# define METACHARACTER	" \t\n|<>"	//" \t\n|&;()<>"

//enum e_here_word
//{
//};
//typedef const struct s_here_word
//{
//	const enum e_here_word	type;
//	const union
//	{
//		
//	};
//}	t_here_word;

///XXX: Single quotes and double quotes behave identically there.
///	Or don't they?	~~lgasc 2024-06-13 17:39
enum e_here_document
{
	HereDocument_Quoteless,
	HereDocument_Quotesome
};
///No need to store the closing delimiter.
///The `word` of the `Quotesome` type is the aftermath of Quote Removal.
///	Remember, Quote Removal also apply the `\` Escape
///		Character and "glue quotes" (such as in `AB'CD'EF`
///		and `''ABC''DEF''`, both equivalent to `ABCDEF`).
///	TODO: Should the word of `<<''` have for representation
///		a `NULL` pointer or an `&'\0'` empty string?
typedef struct s_here_document
{
	enum e_here_document	type;
	char					*word;
}	t_here_document;
typedef t_here_document		t_heredc;

enum e_particle
{
	Particle_Plain,
	Particle_SingleQuote,
	Particle_DoubleQuote,
	Particle_Variable,
	Particle_StatusParameter,
};
typedef struct s_particle
{
	enum e_particle	type;
	union
	{
		char				*plain;
		char				*single_quote;
		t_param_expansible	double_quote;
		t_name				variable;
	};
}				t_particle;
typedef t_particle			t_ptcl;
typedef struct s_particle_node
{
	t_particle				p;
	struct s_particle_node	*next;
}	t_particle_node;
typedef t_particle_node		t_ptclnd;
typedef t_particle_node		t_core	__attribute__	((deprecated));

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
typedef struct s_bond
{
	t_atom			a;
	struct s_bond	*next;
}				t_parse;

enum e_cursor
{
	Cursor_SingleQuote,
	Cursor_DoubleQuote
};
typedef struct s_cursor
{
	t_parse	**p;
	union
	{
		t_slice	**slice;
	};
}	t_cursor	__attribute__	((deprecated));
#endif
