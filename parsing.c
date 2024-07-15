/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:42:43 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/15 00:11:09 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "libft/libft.h"

#include "atom.h"
#include "double_quote.h"

//static t_fail	ft_ready(t_cursor *const cursor, enum e_cursor depth)
//				__attribute__		((warn_unused_result));
//static void		ft_cleanup(void);
static void		ft_copy_into(
					char *destination, const char *source, size_t length);
static t_param_expansible	ft_double_quote(
								const char *text, const size_t length)
				__attribute__	((nonnull, warn_unused_result));
//static bool	ft_single_quote(char **const string, const char* text, size_t *i
//					) __attribute__	((warn_unused_result, nonnull ( 3 , 2 ) ) );
static char		*ft_single_quote(const char *const text)
				__attribute__	((nonnull, warn_unused_result));
static t_wish	ft_wish(const char *const text)
				__attribute__	((nonnull, warn_unused_result));
static void		ft_0spring(t_spring spring);
static void		ft_0expansible(t_param_expansible expansible);
static void		ft_0string(const char *string);
static void		ft_0name(t_name name);
static void		ft_znoop(size_t size);
static void		ft_0size(size_t size);
static size_t	ft__single_quote_cost(void)	__attribute__ ((alias ("ft_find")));
static size_t	ft___plain_text_cost(void) __attribute__ ((warn_unused_result));
static char		*ft_plain_text(void)	__attribute__	((warn_unused_result));

/*__attribute__ ((nonnull))
t_bond	*ft_atomise(const char *const text)
{
	size_t		i;
	size_t		start;
	t_bond		*head;
	t_cursor	cursor;
	bool		error;

	error = false;
	//head = (t_atom_node *){malloc(sizeof * head)};
	//if (head == (t_atom_node *){NULL})
	//	return (ft_cleanup());
	head = (t_bond *){NULL}; //!FIXME: All assumptions on `head`
	i = 0;
	//head->atom.type = -1; //!XXX Enum 😠
	while (text [i] == ' ' || text [i] == '\t' || text [i] == '\n')
		//head->atom.type = (++ i, Atom_Blank);
		++ i;
	cursor.bond	= & head; //!cursor ~> NULL
	//if (head->atom.type == Atom_Blank)
	//	next = & head->next; //!XXX: Dangly!
	// TODO: Loop it. Forget no Blank!
	if (text [i] == '\'')
	///Atom_SingleQuote
	{
		//if (next != & head)
		//	*next = (t_atom_node * const){malloc(sizeof * *next)};
		//if (*next == (t_atom_node *){NULL})
		//	return (ft_cleanup());
		if (ft_ready(& cursor, Cursor_SingleQuote) == ERROR)
			return (ft_cleanup(), VOID);
		///This allocates for the string.
		if (ft_single_quote(& (**cursor.slice).particle.plain_text, text, & i)
			== ERROR)
			return (ft_cleanup(), VOID);
		//cursor. = & (**cursor.c).next; //!XXX: Dangly!
		///i +> '\0' | '\'', cursor ~> Particle_SingleQuote
	}
	else if (text [i] == '"')
	///Atom_DoubleQuote
	{
		if (ft_ready(& cursor, Cursor_DoubleQuote) == ERROR)
			return (ft_cleanup(), VOID);
		//if (ft_double_quote
		//	(&head, (**cursor.slice).particle.double_quote, text, & i) == ERROR)
		//	return (ft_cleanup(), VOID);
		ft_double_quote();
		next = & (**next).next; //!XXX: Dangly!
		///i +> '\0' | '"'
	}
	else if (text [i] == '$')
	{
		if (next != & head)
			*next = (t_atom_node *){malloc(sizeof * (t_atom_node *){*next})};
		if (*next == (t_atom_node *){NULL})
			return (ft_cleanup(), VOID);
		start = ++ i;
		if (text [start] == '?')
		///Atom_StatusParameter
			(**next) = (t_atom_node)
			{{Atom_StatusParameter, (t_cluster){VOID}}, NULL};
			//!i +> '?'
		else if (text [start] != '_' && ! ft_isalpha(text [start]))
		///Atom_PlainText
			(**next) = (t_atom_node)
			{Atom_PlainText, {{& (struct s_cluster){{(char [2]){'$', '\0'}, NULL}}}}, NULL};
			//!i +> ~ ('A'..='Z' | '_' | 'a'..='z')
		else
		///Atom_Variable
		{
			while (text [i] == '_' || ft_isalpha(text [i]))
				++ i;
			(**next) = (t_atom_node)
			{{Atom_Variable, 
			{{Atom_Variable, .variable = {(char *){malloc((i - start + 1)
					* sizeof *(char *){(**next).atom.variable.n})}}}, NULL};
			if ((**next).atom.variable.n == (char *){NULL})
				return (ft_cleanup());
			ft_copy_into((**next).atom.variable.n, text + start, i - start);
			///i +> ~ ('A'..='Z' | '_' | 'a'..='z')
		}
		next = & (**next).next; //!XXX: Dangly!
	}
	else if (text [i] == '<')
	//!TODO: Prefix: file descriptor number or {varname}
	//!	XXX: Nevermind {varname}; that is out of this project scope.
	//!		>Your   shell   should:   \[...]   not   interpret   \[...]  special
	//!		>characters  which  are not  required   by   the   subject   \[...].
	{
		if (next != & head)
			*next = (t_atom_node *){malloc(sizeof * (t_atom_node *){*next})};
		if (*next == (t_atom_node *){NULL})
			return (ft_cleanup());
		(**next) = (t_atom_node){Atom_InputRedirection, NULL, NULL};
		++ i;
		while (text [i] == ' ' || text [i] == '\t' || text [i] == '\n')
			++ i;
		if (text [i] == '<' || text [i] == '>' || text [i] == '|')
			return (ft_cleanup());
		// TODO: Loop until Atom_Blank
		if (text [i] == '\'')
		{
			(**next).atom.input_redirection = (t_cluster)
			{malloc(sizeof * (t_cluster){(**next).atom.input_redirection})};
			if ((**next).atom.input_redirection == (t_cluster){NULL})
				return (ft_cleanup());
			* (**next).atom.input_redirection = (t_fragment){Fragment_SingleQuote, ft_single_quote, NULL};
			if (ft_single_quote((**next).atom.input_redirection.single_quote, text, & i) == true) //!i +> ???
				return (ft_cleanup());
			.input_redirection = string;
		}
		else if (text [i] == '"')
			ft_double_quote(); //!i +> ???
		else if (text [i] == '$')
			ft_parameter(); //!i +> ???
		else
			ft_plain_text(); //!i +> ???
		// TODO
		if (error == true)
			return (ft_cleanup());
	}
	else if (0) // TODO: All kinds of Atom. Forget no `Atom_PlainText`!
		;
	if (error == true)
		return (ft_cleanup());
}*/
///TODO: Separate: There should be a separate function to count the cost.
static t_particle	ft_particle(const char *const text)
{
	if (text [0] == '\'')
		return ((t_particle){Particle_SingleQuote,
			{ft_single_quote(text + 1)}, ft__single_quote_cost()});
	else if (text [0] == '"')
		return ((t_particle){Particle_DoubleQuote,
			.double_quote = ft_double_quote(text + 1, ft_find(text, "\""))});
	else if (text [0] == '$' && text [1] == '?')
		return ((t_particle){Particle_StatusParameter, {NEVER}, 2});
	else if (text [0] == '$' && (ft_isalpha(text [1]) || text [1] == '_'))
		ft_variable((t_slice){text + 1, ft_quark_id(text).cost - 1});
	//else
	//!Including `text [0] == '\0' | '\t' | '\n' | ' '`:
	//!	plain text may have a length of zero.
	//!Also if `text [0] == '$' && text [1] != 'A-Z' | 'a-z' | '_'`
	return ((t_particle)
		{Particle_PlainText, {ft_plain_text()}, ft___plain_text_cost()});
}
//__attribute__ ((alias ("ft_find")))
//static size_t	ft__single_quote_cost();
///The `text` parameter shall point right **after** the opening `'\''` quote.
///Returns `NULL` on allocation error.
static char	*ft_single_quote(const char *const text)
{
	///FIXME: `ft_find(text, "'")`
	char *const	content = (char *)
	{malloc((ft_find(content, "'") + 1) * sizeof * (char *){content})};

	if (content == (char *){NULL})
		return ((char *){NULL});
	ft_copy_into(content, text, ft_find(text, "'"));
	return (content);
}

/*static t_fail	ft_ready(
	const t_cursor *const cursor, const enum e_cursor depth)
{
	if (cursor == (t_cursor *const){NULL})
		return (ERROR);
	if (cursor->bond == (t_bond *){NULL})
	{
		*cursor = (t_cursor)
			{.bond = (t_bond *){malloc(sizeof * (t_bond *){cursor->bond})}};
		if (cursor->bond == (t_bond *){NULL})
			return (ERROR);
		//assert(depth == Cursor_SingleQuote || depth == Cursor_DoubleQuote)
		*cursor->bond = (t_bond){{Atom_Field, .field = NULL}, NULL};
		cursor->slice = cursor->bond->atom.field;
		//if (depth == Cursor_Molecule)	return (OK);
	}
	///depth == Cursor_SingleQuote | Cursor_DoubleQuote
	//assert(cursor->bond->atom.type == Atom_Field); //!t_slice	t_atom:.field;
	if (cursor->slice == (t_slice *){NULL})
		cursor->slice = (t_slice){(t_core)
		{malloc(sizeof * (t_core){cursor->bond->atom->field})}, NULL};
	if (cursor->slice == (t_slice *){NULL})
		return (ERROR);
	if (depth == Cursor_SingleQuote)
		*cursor->slice
			= (t_slice){Particle_SingleQuote, .single_quote = DIRT}, NULL};
	else if (depth == Cursor_DoubleQuote)
		*cursor->slice
			= (t_slice){Particle_DoubleQuote, .double_quote= DIRT}, NULL};
	else
		cursor->slice = cursor->slice.next;
	// TODO
	return (OK);
	if (cursor->cluster == (t_cluster){NULL})
		cursor->cluster = (t_atom_node){{Atom_Field, .field}};
	// TODO
	if (cursor->molecule->field == (t_cluster){NULL})
		return (ERROR);
	*cursor->molecule->field = (t_fragment){Fragment_SingleQuote};
	{
		if (depth == Cursor_SingleQuote)
		{
			cur
		}
		//\*cursor->molecule = (t_atom_node){};
		// TODO
	}
	cursor;
	// TODO
	return ;
	if (cursor->type == Cursor_Molecule)
		cursor->molecule
			= (t_molecule){malloc(sizeof * (t_molecule){cursor->molecule})};
	else if (cursor->type == Cursor_Cluster)
		cursor->cluster
			= (t_cluster){malloc(sizeof * (t_cluster){cursor->cluster})};
	else
		//!TODO: All cursor types
		return ;
	///TODO: All cursor types
	if ((cursor->type == Cursor_Molecule && cursor->molecule
			== (t_molecule){NULL}) || (cursor->type == Cursor_Cluster
			&& cursor->cluster == (t_cluster){NULL}))
		return (true);
	return (false);
}*/

///TODO: Use a `libft` function instead.
static void	ft_copy_into(char *const restrict destination,
	const char *restrict const source, const size_t length)
{
	size_t	i;

	if (destination == (char *){NULL} || source == (char *){NULL}
		|| length == 0)
		return ;
	i = 0;
	while (i < length && source [i] != '\0')
	{
		destination [i] = source [i];
		++ i;
	}
	destination [i] = '\0';
}

///As a mean of error propagation, `expansible.simple_text`
///	and `expansible.variable` may be `NULL`.
///TODO: Separate: There should be a separate function to count the cost.
static t_param_expansible	ft_double_quote(
	const char *const text, const size_t length)
{
	const t_wish					wish = ft_wish(text);
	const t_param_expansible		double_quote = ft_param_expansible(wish);
	const t_param_expansible *const	next = ft_next();

	if (wish.type == Quark_SimpleText && wish.cost == 0)
		return ((t_spring){double_quote, 0});
	ft_probe(text + wish.cost);
	//next = ft_double_quote(text + wish.cost, length - wish.cost);
	if (next.cost == 0)
		return (ft_0spring(next), (t_spring){double_quote, wish.cost});
	//double_quote.next = next.expansible;
	return ((t_spring){{double_quote, next.expansible}, wish.cost + next.cost});
}

///On error, `simple_text` and `variable` will be `NULL`.
///It is no error for `simple_text` to have a length of `0`.
static t_wish	ft_wish(const char *const text)
{
	const t_quid	quid = ft_quark_id(text);

	if (quid.type == Quark_SimpleText)
		return ((t_wish){Quark_SimpleText,
		{ft_simple_text(text, quid.length)}, quid.length});
	if (quid.type == Quark_Variable)
		return ((t_wish){Quark_Variable,
		{ft_variable(text + 1, quid.length - 1)}, quid.length});
	if (quid.type == Quark_Status)
		return ((t_wish){Quark_Status, VOID, quid.length});
}

void	ft_0spring(const t_spring spring)
{
	ft_0expansible(spring.expansible);
	ft_0size(spring.cost);
}
void	ft_0expansible(const t_param_expansible expansible)
{
	if (expansible.type == Quark_SimpleText
		&& expansible.simple_text != (char *){NULL})
		ft_0string(expansible.simple_text);
	else if (expansible.type == Quark_Variable)
		ft_0name(expansible.name);
	else if (expansible.type == Quark_Status)
		ft_noop();
	if (expansible.next != (t_param_expansible *){NULL})
		(ft_0expansible(expansible.next),
			free((t_param_expansible *){expansible.next}));
}
__attribute__	((alias ("free")))
void	ft_0string(const char *const string);
//{free((char *){string});}
void	ft_0name(const t_name name)
{
	if (name.n != (char *){NULL})
		ft_0string(name.n);
}
void	ft_znoop(const size_t size)
{
}
__attribute__	((alias	("ft_znoop")))
void	ft_0size(const size_t size);
//{ft_noop();}
void	ft_probe(const char *const text)
{
	ft_quark_id(text);
}

//\///If the allocation fails, the return is `NULL`
//static char	*ft_single_quote(const char *const text, size_t *const i)
//	///*i +> '\''
//{
//	const size_t	start = ++ *i;
//	char			*string;
//
//	while (text [*i] != '\0' && text [*i] != '\'')
//		++ *i;
//	string = (char *){malloc((*i - start + 1) * sizeof * (char *){string})};
//	if (string != (char *){NULL})
//		ft_copy_into(string, text + start, *i - start);
//	return (string);
//	///*i +> '\0' | '\''
//}
