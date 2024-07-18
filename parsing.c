/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:42:43 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/18 06:15:00 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "atom.h"
#include "double_quote.h"

void			ft_free_parse(t_parse p);
static size_t	ft_atom_cost(const char *const s)
				__attribute__	((nonnull,	warn_unused_result));
static size_t	ft_here_word_cost(const char *const s)
				__attribute__	((nonnull,	warn_unused_result));
static t_atom	ft_atom(const char *s)
				__attribute__	((nonnull,	warn_unused_result));
static void		ft_free_atom(t_atom a);
static t_atom	ft_error_atom(void)	__attribute__	((warn_unused_result));
static t_heredc	ft_here_document(const char *text)
				__attribute__	((nonnull,	warn_unused_result));
static void		ft_free_heredoc(t_here_document h);
static size_t	ft_here_word_length(const char *s)
				__attribute__	((nonnull,	warn_unused_result));
static t_ptclnd	ft_particle_node(const char *text)
				__attribute__	((nonnull,	warn_unused_result));
static void		ft_0particle_node(t_particle_node n);
static size_t	ft_particle_cost(const char *s)
				__attribute__	((nonnull,	warn_unused_result));
static t_ptcl	ft_particle(const char *s)
				__attribute__	((nonnull,	warn_unused_result));
static void		ft_0particle(t_particle p);
static size_t	ft_plain_cost(const char *s)
				__attribute__	((nonnull,	warn_unused_result));
//static t_fail	ft_ready(t_cursor *const cursor, enum e_cursor depth)
//				__attribute__		((warn_unused_result));
//static void		ft_cleanup(void);
static void		ft_copy_into(
					char *destination, const char *source, size_t length);
static t_prmxpn	ft_double_quote(const char *text)
				__attribute__	((nonnull, warn_unused_result));
//static bool	ft_single_quote(char **const string, const char* text, size_t *i
//					) __attribute__	((warn_unused_result, nonnull ( 3 , 2 ) ) );
static char		*ft_single_quote(const char *const text)
				__attribute__	((nonnull, warn_unused_result));

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
			(**next) = (t_atom_node){Atom_PlainText,
				{{& (struct s_cluster){{(char [2]){'$', '\0'}, NULL}}}}, NULL};
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
			* (**next).atom.input_redirection
				= (t_fragment){Fragment_SingleQuote, ft_single_quote, NULL};
			if (ft_single_quote((**next).atom.input_redirection.single_quote,
					text, & i) == true) //!i +> ???
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

///Shall `field.plain_text` be `NULL` on allocation error.
__attribute__	((nonnull,	warn_unused_result))
t_parse	ft_parse(const char *const s)
{
	t_parse *const	next = (t_parse *){malloc(sizeof * (t_parse *){next})};
	const char		*si;
	t_atom			a;

	si = s + ft_span(s, BLANK);
	if (*si == '\0')
		return ((t_parse)
			{{Atom_Field, .field = {{Particle_Plain, .plain = (char *){NULL}},
					(t_ptclnd *){NULL}}}, (t_parse *){NULL}});
	a = ft_atom(si);
	if ((a.type == Atom_HereDocument && a.here_document.word == (char *){NULL})
		|| (a.type == Atom_Input && a.input.p.type
			== Particle_Plain && a.input.p.plain
			== (char *){NULL}) || (a.type == Atom_Appending
			&& a.appending.p.type == Particle_Plain
			&& a.appending.p.plain == (char *){NULL})
		|| (a.type == Atom_Output && a.output.p.type
			== Particle_Plain && a.output.p.plain
			== (char *){NULL}) || (a.type == Atom_Field && a.field.p.type
			== Particle_Plain && a.field.p.plain == (char *){NULL}))
		return (ft_free_atom(a), (t_parse){{Atom_Field, .field = {{
						Particle_Plain, .plain = (char *){NULL}},
				(t_ptclnd *){NULL}}}, (t_parse *){NULL}});
	si += ft_atom_cost(si) + ft_span(s, BLANK);
	if (*si == '\0')
		return ((t_parse){a, (t_parse *){NULL}});
	if (next == (t_parse *){NULL})
		return (ft_free_atom(a), (t_parse){{Atom_Field, .field = {{
						Particle_Plain, .plain = (char*){NULL}},
				(t_ptclnd *){NULL}}}, (t_parse *){NULL}});
	*next = ft_parse(si);
	if (next->a.type == Atom_Field && next->a.field.p.type == Particle_Plain
		&& next->a.field.p.plain == (char *){NULL})
		return (ft_free_atom(a), ft_free_parse(*next), free((t_parse *){next}),
(t_parse){{Atom_Field, .field = {{Particle_Plain, .plain = (char *){NULL}},
(t_ptclnd *){NULL}}}, (t_parse *){NULL}});
	return ((t_parse){a, next});
}

void	ft_free_parse(const t_parse p)
{
	ft_free_atom(p.a);
	if (p.next != (t_parse *){NULL})
		(ft_free_parse(*p.next), free((t_parse *){NULL}));
}

static size_t	ft_atom_cost(const char *const s)
{
	if (*s == '|')
		return (1);
	else if (*s == '<' && s [1] == '<')
		return (2 + ft_span(s + 2, BLANK) + (s [2 + ft_span(s + 2, BLANK)]
				!= '\0') * ft_here_word_cost(s + 2 + ft_span(s + 2, BLANK)));
	else if (*s == '>' && s [1] == '>')
		return (2 + ft_span(s + 2, BLANK)
			+ ft_particle_cost(s + 2 + ft_span(s + 1, BLANK)));
	else if (*s == '<' || *s == '>')
		return (1 + ft_span(s + 1, BLANK)
			+ ft_particle_cost(s + 1 + ft_span(s + 1, BLANK)));
	else
		return (ft_particle_cost(s));
}

static size_t	ft_here_word_cost(const char *const s)
{
	size_t	cost;

	cost = 0;
	while (s [cost] == '\0')
	{
		if (s [cost] == '\0')
			return (cost);
		else if (s [cost] == '"' && (++ cost, true))
			while (s [cost] != '\0' && (s [cost] != '"' || (++ cost, false)))
				++ cost;
		else if (s [cost] == '\'' && (++ cost, true))
			while (s [cost] != '\0' && (s [cost] != '\'' || (++ cost, false)))
				++ cost;
		else
		{
			cost += ft_find(s + cost, "\"'" METACHARACTER);
			if (ft_strchr(METACHARACTER, s [cost]))
				return (cost);
		}
	}
	return (cost);
}

///The `text` parameter shall point to the
///	first (non-blank) character of the atom.
///The `here_document.word`, `input_redirection.p.plain_text`,
///	`appending_redirection.p.plain_text`, `output_redirection.p.plain_text`,
///	or `field.p.plain_text` shall be `NULL` on allocation error.
static t_atom	ft_atom(const char *const s)
{
	t_atom	a;

	if (*s == '|')
		return ((t_atom)
			{Atom_Pipe, {{{Particle_Plain, {NEVER}}, (t_ptclnd *){NULL}}}});
	else if (*s == '<' && s [1] == '<')
		a = (t_atom){Atom_HereDocument,
			.here_document = ft_here_document(s + 2 + ft_span(s + 2, BLANK))};
	else if (*s == '<')
		a = (t_atom)
		{Atom_Input, .input = ft_particle_node(s + 1 + ft_span(s + 1, BLANK))};
	else if (*s == '>' && s [1] == '>')
		a = (t_atom){Atom_Appending,
			.appending = ft_particle_node(s + 2 + ft_span(s + 2, BLANK))};
	else if (*s == '>')
		a = (t_atom){Atom_Output,
			.output = ft_particle_node(s + 1 + ft_span(s + 1, BLANK))};
	if ((*s == '<' && s [1] == '<' && a.here_document.word == (char *){NULL})
		|| (*s == '<' && s [1] != '<' && a.input.p.type == Particle_Plain && a
			.input.p.plain == (char *){NULL}) || (*s == '>' && s[1] == '>' && a
			.appending.p.type == Particle_Plain && a.appending.p.plain
			== (char *){NULL}) || (*s == '>' && s [1] != '>' && a.output.p.type
			== Particle_Plain && a.output.p.plain == (char *){NULL}))
		return (ft_free_atom(a), ft_error_atom());
	else if (*s != '<' && *s != '>')
		a = (t_atom){Atom_Field, .field = ft_particle_node(s)};
	return (a);
}

static void	ft_free_atom(const t_atom a)
{
	if (a.type == Atom_Field)
		ft_0particle_node(a.field);
	else if (a.type == Atom_Input)
		ft_0particle_node(a.input);
	else if (a.type == Atom_Output)
		ft_0particle_node(a.output);
	else if (a.type == Atom_Appending)
		ft_0particle_node(a.appending);
	else if (a.type == Atom_HereDocument)
		ft_free_heredoc(a.here_document);
}

static t_atom	ft_error_atom(void)
{
	return ((t_atom){Atom_Field, .field
		= {{Particle_Plain, .plain = (char *){NULL}}, (t_ptclnd *){NULL}}});
}

///The `delimiter` may be the empty string. (It then matches an empty line.)
///For the scope of this `minishell` project, there
///	is no support for the `'\\'` Escape Character.
///Returns `NULL` on allocation error.
static t_heredc	ft_here_document(const char *const text)
{
	char *const				word = (char *)
	{malloc((ft_here_word_length(text) + 1) * sizeof * (char *){word})};
	enum e_here_document	quote;
	const char				*ti;
	char					*wi;

	if (word == (char *){NULL})
		return ((t_heredc){-1, NULL});
	quote = HereDocument_Quoteless;
	ti = text;
	wi = word;
	while (*ti != '\0' && ! ft_strchr(METACHARACTER, *ti))
		if (quote == HereDocument_Quoteless && (*ti == '"' || *ti == '\''))
			quote = HereDocument_Quotesome;
	else if (*ti == '"')
		while (*++ ti != '\0' && (*ti != '"' || (++ ti, false)))
			*wi ++ = *ti;
	else if (*ti == '\'')
		while (*++ ti != '\0' && (*ti != '\'' || (++ ti, false)))
			*wi ++ = *ti;
	else
		while (*ti != '\0' && ! ft_strchr("\"'" METACHARACTER, *ti))
			*wi ++ = *ti ++;
	*wi = '\0';
	return ((t_heredc){quote, word});
}

static void	ft_free_heredoc(t_here_document h)
{
	if (h.word != (char *){NULL})
		free((char *){h.word});
}

static size_t	ft_here_word_length(const char *const s)
{
	size_t		length;
	const char	*si;

	length = 0;
	si = s;
	while (*si != '\0' && ! ft_strchr("\"'" METACHARACTER, *si))
		if (*si == '"')
			while (*++ si != '\0' && (*si != '"' || (++ si, false)))
				++ length;
	else if (*si == '\'')
		while (*++ si != '\0' && (*si != '\'' || (++ si, false)))
			++ length;
	else
		while (*si != '\0' && ! ft_strchr("\"'" METACHARACTER, *si))
			length += (++ si, 1);
	return (length);
}

///The `plain_text` shall be `NULL` on allocation error.
static t_ptclnd	ft_particle_node(const char *const text)
{
	const t_particle		p = ft_particle(text);
	t_particle_node *const	next
		= (t_ptclnd *){malloc(sizeof * (t_ptclnd *){next})};

	if ((ft_strchr(METACHARACTER, text [ft_particle_cost(text)])
			&& next == (t_ptclnd *){NULL})
		|| (p.type == Particle_Plain && p.plain == (char *){NULL})
		|| (p.type == Particle_SingleQuote && p.single_quote == (char *){NULL})
		|| (p.type == Particle_DoubleQuote && p.double_quote.q.type
			== Quark_Simple && p.double_quote.q.simple == (char *){NULL})
		|| (p.type == Particle_Variable && p.variable.n == (char*){NULL}))
		return (ft_0particle(p), free((t_ptclnd *){next}), (t_ptclnd){{
			Particle_Plain, .plain = (char *){NULL}}, (t_ptclnd *){NULL}});
	if (ft_strchr(METACHARACTER, text [ft_particle_cost(text)]))
		return ((t_ptclnd){p, (t_ptclnd *){NULL}});
	*next = ft_particle_node(text + ft_particle_cost(text));
	if (next->p.type == Particle_Plain && next->p.plain == (char *){NULL})
		return (ft_0particle(p), ft_0particle_node(*next),
			free((t_ptclnd *){next}), (t_ptclnd){{Particle_Plain,
			.plain = (char *){NULL}}, (t_ptclnd *){NULL}});
	return ((t_ptclnd){p, next});
}

static void	ft_0particle_node(const t_particle_node n)
{
	ft_0particle(n.p);
	if (n.next != (t_particle_node *){NULL})
		(ft_0particle_node(*n.next), free((t_particle_node *){n.next}));
}

static size_t	ft_particle_cost(const char *const s)
{
	if (*s == '\'')
		return (1 + ft_find(s + 1, "'") + 1);
	else if (*s == '"')
		return (1 + ft_find(s + 1, "\"") + 1);
	else if (*s == '$' && s [1] == '?')
		return (2);
	else if (*s == '$' && (s [1] == '_' || ft_isalpha(s [1])))
		return (1 + ft_span(s + 2, DIGIT CAPITAL "_" SMALL));
	else if (*s == '\0' || ft_strchr(METACHARACTER, *s))
		return (0);
	else
		return (ft_plain_cost(s));
}

///A `Particle_PlainText` may have a `cost` of 0, this is no error.
///	In this case, the `plain_text` shall be the `""` empty string literal.
///		Remember, you shall not `free` a string literal!
///TODO: Separate: There should be a separate function to count the cost.
///TODO: `plain_text` should absorb surrounding non-parameter `'$'`;
///	this currently produce consecutive `plain_text` from
///	text such as `"abc$+de"` (`"abc"`, `"$"`, and `"de"`)
///	while the result should be a single `plain_text`.
//else // Also if `text [0] == '$' && text [1] != 'A-Z' | 'a-z' | '_'`
static t_particle	ft_particle(const char *const text)
{
	if (text [0] == '\'')
		return ((t_particle){Particle_SingleQuote,
			{ft_single_quote(text + 1)}, //1 + ft_find(text + 1, "'") + 1
		});
	else if (text [0] == '"')
		return ((t_particle){Particle_DoubleQuote, .double_quote
			= ft_double_quote(text + 1//, ft_find(text,"\"") + ?
			)});
	else if (text [0] == '$' && text [1] == '?')
		return ((t_particle){Particle_StatusParameter, {NEVER}});
	else if (text [0] == '$' && (ft_isalpha(text [1]) || text [1] == '_'))
		ft_variable((t_slice)
			///FIXME: `strspn`/`ft_span` UB when all match
		{text + 1, 1 + ft_span(text + 2, DIGIT CAPITAL "_" SMALL)});
	else if (text [0] == '\0'
		|| ft_strchr(METACHARACTER, text [0]) != (char *){NULL})
		return ((t_particle){Particle_Plain, {""}});
	return ((t_particle){
		Particle_Plain, {ft_plain_text((t_slice){text, ft_plain_cost(text)})}});
}

static void	ft_0particle(const t_particle p)
{
	if (p.type == Particle_Plain && p.plain != (char *){""})
		free((char *){p.plain});
	else if (p.type == Particle_SingleQuote && p.single_quote != (char *){""})
		free((char *){p.single_quote});
	else if (p.type == Particle_DoubleQuote)
		ft_0expansible(p.double_quote);
	else if (p.type == Particle_Variable)
		ft_0name(p.variable);
}
//__attribute__ ((alias ("ft_find")))
//static size_t	ft__single_quote_cost();

///For the scope of this `minishell` project, there
///	is no support for the `'\\'` Escape Character.
static size_t	ft_plain_cost(const char *const s)
{
	return (ft_find(s, "\"$'" METACHARACTER));
}

///The `text` parameter shall point right **after** the opening `'\''` quote.
///Returns `NULL` on allocation error.
static char	*ft_single_quote(const char *const text)
{
	char *const	content = (char *)
		///FIXME: `ft_find(text, "'")` UB if none found
	{malloc((ft_find(text, "'") + 1) * sizeof * (char *){content})};

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

///The `text` parameter shall point _after_ the `'"'` opening double quote.
///As a mean of error propagation, `expansible.simple_text`
///	and `expansible.variable` may be `NULL`.
///TODO: Separate: There should be a separate function to count the cost.
static t_param_expansible	ft_double_quote(const char *const text)
{
	const t_param_expansible		double_quote = ft_param_expansible(text);

	return (double_quote);
}
//{free((char *){string});}

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
