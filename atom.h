/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:07:26 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/14 20:57:00 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  ATOM_H
# define ATOM_H

# include <stdbool.h>

# include "quark.h"

///Explicit discard with `VOID`:
///	Use of `NULL` may indicate a field as incomplete, as awaiting for a value.
///	`NEVER` marks a field as "complete" - such pointer shall have no use.
///	`DIRT` acts as an _explicit_ placeholder value. Dirty!
# define NEVER	NULL
# define VOID	NEVER	//!Depreciated: Rename to `NEVER`.
# define IVOID	-1		//!Depreciated; maybe use `(int)VOID`?
# define DIRT	NULL	//!Depreciated

typedef bool	t_fail;
# define OK		false
# define ERROR	true

///Word Splitting only occurs where parameters are expund outside of quotes;
///	It is not the concern of non-parameter text and expansions within quotes.
///`Quark_Status` has no visible value in
///	the `union` as it is a unitary marker.
///`simple_text` may be empty ({'\0'}) and thus have a `cost` of `0`.
///`simple_text` and `variable` will be `NULL` on error.
typedef struct s_expansible
{
	const enum e_quark					type;
	union
	{
		char *const		simple_text;
		const t_name	variable;
	};
	const struct s_expansible *const	next;
}	t_param_expansible;
typedef struct s_spring
{
	const t_param_expansible	expansible;
	const size_t				cost;
}	t_spring;

///XXX: Single quotes and double quotes behave identically there.
///	Or don't they?	~~lgasc 2024-06-13 17:39
enum e_here_document
{
	HereDocument_Quoteless,
	HereDocument_Quotesome
};
///No need to store the closing delimiter.
///The `word` of the `Quotesome` type is the aftermath of Quote Removal.
///	Remember, Quote Removal also apply to `\` Escape
///		Characters and "glue quotes" (such as in `AB'CD'EF`
///		and`''ABC''DEF''`, both equivalent to `ABCDEF`).
///	TODO: Should the word of `<<''` have for representation
///		a `NULL` pointer or an `&'\0'` empty string?
typedef struct s_here_document
{
	enum e_here_document	type;
	char					*word;
	union
	{
		t_param_expansible	quoteless_document;
		char				*quotsome_document;
	};
}				t_here_document;

enum e_particle
{
	Particle_PlainText,
	Particle_SingleQuote,
	Particle_DoubleQuote,
	Particle_Variable,
	Particle_StatusParameter,
};
typedef struct s_particle
{
	const enum e_particle	type;
	const union
	{
		const char *const			plain_text;
		const char *const			single_quote;
		const t_param_expansible	double_quote;
		const t_name				variable;
	};
	const size_t			cost;
}				t_particle;
//typedef struct s_slice
//{
//	t_particle		particle;
//	struct s_slice	*next;
//}				t_slice;
typedef t_slice	*t_core __attribute__	((deprecated));

enum e_atom
{
	//Atom_Blank,
	//Atom_PlainText,
	//Atom_SingleQuote,
	//Atom_DoubleQuote,
	//Atom_Variable,
	//Atom_StatusParameter,
	Atom_Field,
	Atom_InputRedirection,
	Atom_OutputRedirection,
	Atom_HereDocument,
	Atom_AppendingRedirection,
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
		//char				*plain_text;
		//char				*single_quote;
		//t_param_expansible	*double_quote;
		//t_name				variable;
		t_slice				*field;
		t_slice				*input_redirection;
		t_slice				*output_redirection;
		t_here_document		here_document;
		t_param_expansible	appending_redirection;
	};
}				t_atom;
typedef struct s_bond
{
	t_atom			atom;
	struct s_bond	*next;
}				t_bond;
//typedef t_bond	*t_molecule __attribute__ ((deprecated));

enum e_cursor
{
	Cursor_SingleQuote,
	Cursor_DoubleQuote
};
typedef struct s_cursor
{
	t_bond	**bond; //!`t_bond &`, not `t_molecule`
	union
	///Depending on the molecule/atom type
	{
	//	struct
	//	{
		t_slice	**slice;
	//		//union
	//		//\///Depending on the cluster/fragment type
	//		//{};
	//	};
	};
}	t_cursor;
#endif
