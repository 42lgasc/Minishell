/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:59:45 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/15 15:03:12 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quark.h"

__attribute__	((nonnull, warn_unused_result))
bool	ft_is_at_end(const size_t start, const size_t i, const char *const text)
{
	if (text [start] == '$' && text [start + 1] == '?' && i == start + 2)
		return ("STATUS PARAMETER", true);
	if (text [start] == '$' && i == start + 1
		&& ! ft_isalpha(text [i]) && text [i] != '_')
		return ("FALLBACK LITERAL SIGN", true);
	if (text [start] == '$' && i > start + 1
		&& ! ft_isalnum(text [i]) && text [i] != '_')
		return ("END OF VARIABLE", true);
	if (i == start && (text [i] == '\0' || text [i] == '"'))
		return ("NO MORE");
	if (text [i] == '\0' || text [i] == '"'
		|| (text [start] != '$' && text [i] == '$'))
		return ("END OF SIMPLE TEXT", true);
	return (false);
}

///The `text` parameter shall point _after_ the opening `'"'` double quote.
///The `cost` is the amount of characters which represents
///	a quark; The amount of meaningful characters may
///	be lesser due to affix markers such as `'$'`.
///A `Quark_SimpleText` may have a cost of `0`: This
///	means there are no more characters. Quarks of other
///	type may be last, but only this one can have no cost.
__attribute__	((nonnull, warn_unused_result))
t_quid	ft_quark_id(const char *const text)
{
	size_t	cost;

	if (text [0] == '\0' || text [0] == '"')
		return ((t_quid){Quark_SimpleText, 0});
	if (text [0] == '$' && text [1] == '?')
		return ((t_quid){Quark_Status, 2});
	if (text [0] == '$' && ! ft_isalpha(text [1]) && text [1] != '_')
		return ((t_quid){Quark_SimpleText, 1});
	length = 1;
	while (text [cost] != '\0' && text [cost] != '"' && text [cost] != '$')
		if (text [0] == '$' && cost >= 2
			&& ! ft_isalnum(text [cost]) && text [cost] != '_')
			return ((t_quid){Quark_Variable, cost});
	else
		++ length;
	return ((t_quid){Quark_SimpleText, cost});
}

__attribute__	((nonnull, restrict, warn_unused_result))
bool	ft_plain_text(t_PEN **const pen, size_t const start,
	size_t const i, const char *const text)
{
	*pen = (t_PEN *){malloc(sizeof * (t_PEN *){*pen})};
	if (*pen == (t_PEN *){NULL})
		return (true);
	**pen = (t_PEN){PEN_SimpleText, {(char *)
	{malloc((i - start + 1) * sizeof * (char *){(**pen).simple_text})}}, NULL};
	if ((**pen).simple_text == (char *){NULL})
		return (true);
	ft_copy_into((**pen).simple_text, text + start, i - start);
	return (false);
}

///Returns: A strind (with maybe zero length), or `NULL` on allocation error
__attribute__	((nonnull, warn_unused_result))
char	*ft_plain_text(const t_slice slice)
{
	char *const	simple
		= (char *){malloc((length + 1) * sizeof * (char *){simple})};
	size_t		i;

	if (text == (char *){NULL} || simple == (char *){NULL})
		return (free((char *){simple}), (char *){NULL});
	i = 0;
	while (i < length)
	{
		simple [i] = text [i];
		++ i;
	}
	simple [i] = '\0';
	return (simple);
}

///`next_pen`: A reference to a field which is a pointer with no allocation yet.
__attribute__	((nonnull, warn_unused_result))
bool	ft_fallback_literal_sign(t_PEN **const pen)
{
	*pen = (t_PEN *){malloc(sizeof * (t_PEN *){*pen})};
	if (*pen == (t_PEN *){NULL})
		return (true);
	**pen = (t_PEN){PEN_SimpleText,
	{(char *){malloc(2 * sizeof * (char *){(**pen).simple_text})}}, NULL};
	if ((**pen).simple_text == (char *){NULL})
		return (true);
	(**pen).simple_text = (char [2]){'$', '\0'};
	return (false);
}

__attribute__	((nonnull, warn_unused_result))
bool	ft_status_parameter(t_PEN **const pen)
{
	*pen = (t_PEN *){malloc(sizeof * (t_PEN *){*pen})};
	if (*pen == (t_PEN *){NULL})
		return (true);
	**pen = (t_PEN){PEN_Status, (char *){VOID}, NULL};
	return (false);
}

__attribute__	((nonnull, warn_unused_result))
static bool	ft_variable(t_PEN **const pen, const size_t start,
	const size_t i, const char *const text)
{
	*pen = (t_PEN *){malloc(sizeof * (t_PEN *){*pen})};
	if (*pen == (t_PEN *){NULL})
		return (true);
	**pen = (t_PEN){PEN_Variable, .variable = {(char *)
	{malloc((i - start) * sizeof * (char *){(**pen).variable.n})}}, NULL};
	if ((**pen).variable.n == (const char *){NULL})
		return (true);
	ft_copy_into((**pen).variable.n, text + start, i - start);
	return (false);
}

///The `slice` shall exclude the parameter sign
///	and optional braces (`'$'`, `'{'`, `'}'`).
///Returns: The name, with its own allocation, or `NULL` on error
__attribute__	((nonnull, warn_unused_result))
t_name	ft_variable(//const char *const name, const size_t length
	const t_slice name)
{
	const t_name	variable
		= {(char *){malloc((length + 1) * sizeof * (char *){variable.n})}};
	size_t			i;

	if (name.string == (char *){NULL} || variable.n == (char *){NULL})
		return (free((char *){variable.n}), (char *){NULL});
	i = 0;
	while (i < name.length)
	{
		variable.n [i] = name.string [i];
		++ i;
	}
	variable.n [i] = '\0';
	return (variable);
}

///The `text` parameter shall point _after_ the `'"'` opening double quote.
///Shall an error occur, `simple_text` or `variable.n` will be `NULL`.
///	As of now, `next` would then also be `NULL`.
///It is not an error for `simple_text` to have a length of `0`:
///	This is one of the ways to mark the end.
t_param_expansible	ft_param_expansible(const t_wish wish)
{
	const t_wish	wish = ft_wish(text);

	if ((wish.type == Quark_SimpleText && wish.simple_text == (char *){NULL})
		|| wish.type == Quark_Variable && wish.variable.n == (char *){NULL})
		return ((t_param_expansible){wish.quark, NULL});
	if (wish.type = Quark_SimpleText && wish.cost == 0)
		return ((t_param_expansible){wish.quark, NULL});
	if (wish.type == Quark_SimpleText)
		double_quote = (t_param_expansible)
		{Quark_SimpleText, {wish.simple_text}, ft_next()};
	else if (wish.type == Quark_Variable)
		double_quote = (t_param_expansible)
		{Quark_Variable, .variable = wish.variable, ft_next()};
	else if (wish.type == Quark_Status)
		double_quote = (t_param_expansible){Quark_Status, NEVER, ft_next()};
}

///Returns `NULL` on allocation error.
static t_param_expansible	*ft_next(
	const t_wish wish, const char *const text, const size_t length)
{
	const t_wish				wish = ft_wish();
	t_param_expansible *const	next
		= (t_param_expansible *){malloc(sizeof * (t_param_expansible *){next})};

	if (next == (t_param_expansible *){NULL})
		return (ft_0wish(), (t_param_expansible *){NULL});
	if (wish.type == Quark_SimpleText && wish.cost == 0)
		*next = (t_param_expansible)
		{wish.type, {wish.simple_text}, (t_param_expansible *){NULL}});
	if (wish.type == Quark_SimpleText && wish.cost == 0)
		return (next);
	if (wish.type == Quark_SimpleText)
		*next = (t_param_expansible)
		{wish.type, {wish.simple_text}, ft_next(text + wish.cost)};
	else if (wish.type == Quark_Variable)
		*next = (t_param_expansible)
		{wish.type, {wish.variable}, ft_next(text + wish.cost)};
	else if (wish.type == Quark_Status)
		*next
			= (t_param_expansible){wish.type, NEVER, ft_next(text + wish.cost)};
	if (next->next == NULL) //!Except if `wish == {Quark_SimpleText, 0}`
		return (
			ft_0wish(wish), ft_0expansible(next), (t_param_expansible *){NULL});
	return (next);
}

///The `text` parameter shall point _after_ the `'"'` opening double quote.
///On error, `simple_text` and `variable` will be `NULL`.
///It is no error for `simple_text` to have a length of `0`.
///TODO: Separate: There should be different functions for
///	identifying type, counting cost, and assembling the structure.
t_wish	ft_wish(const char *const text)
{
	const t_quid	quid = ft_quark_id(text);

	if (quid.type == Quark_SimpleText)
		return ((t_wish){Quark_SimpleText,
		{ft_plain_text(text, quid.length)}, quid.length});
	if (quid.type == Quark_Variable)
		return ((t_wish){Quark_Variable,
		{ft_variable(text + 1, quid.length - 1)}, quid.length});
	if (quid.type == Quark_Status)
		return ((t_wish){Quark_Status, VOID, quid.length});
}
