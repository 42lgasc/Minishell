/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:59:45 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/18 06:11:26 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft/libft.h"

#include "quark.h"

static t_prmxpn	*ft_next(const char *const text)
				__attribute__	((nonnull,	warn_unused_result));
static void		ft_0wish(const t_wish w);
static void		ft_0quark(t_quark quark);

__attribute__	((nonnull, warn_unused_result))
bool	ft_is_at_end(const size_t start, const size_t i, const char *const text)
{
	if (text [start] == '$' && text [start + 1] == '?' && i == start + 2)
		return (true);
	if (text [start] == '$' && i == start + 1
		&& ! ft_isalpha(text [i]) && text [i] != '_')
		return (true);
	if (text [start] == '$' && i > start + 1
		&& ! ft_isalnum(text [i]) && text [i] != '_')
		return (true);
	if (i == start && (text [i] == '\0' || text [i] == '"'))
		return ("NO MORE");
	if (text [i] == '\0' || text [i] == '"'
		|| (text [start] != '$' && text [i] == '$'))
		return (true);
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
		return ((t_quid){Quark_Simple, 0});
	if (text [0] == '$' && text [1] == '?')
		return ((t_quid){Quark_Status, 2});
	if (text [0] == '$' && ! ft_isalpha(text [1]) && text [1] != '_')
		return ((t_quid){Quark_Simple, 1});
	cost = 1;
	while (text [cost] != '\0' && text [cost] != '"' && text [cost] != '$')
		if (text [0] == '$' && cost >= 2
			&& ! ft_isalnum(text [cost]) && text [cost] != '_')
			return ((t_quid){Quark_Variable, cost});
	else
		++ cost;
	return ((t_quid){Quark_Simple, cost});
}

//__attribute__	((nonnull, restrict, warn_unused_result))
//bool	ft_plain_text(t_PEN **const pen, size_t const start,
//	size_t const i, const char *const text)
//{
//	*pen = (t_PEN *){malloc(sizeof * (t_PEN *){*pen})};
//	if (*pen == (t_PEN *){NULL})
//		return (true);
//	**pen = (t_PEN){PEN_SimpleText, {(char *)
//	{malloc((i - start + 1) * sizeof * (char *){(**pen).simple_text})}}, NULL};
//	if ((**pen).simple_text == (char *){NULL})
//		return (true);
//	ft_copy_into((**pen).simple_text, text + start, i - start);
//	return (false);
//}

///Returns: A strind (with maybe zero length), or `NULL` on allocation error
__attribute__	((warn_unused_result))
//!nonnull
char	*ft_plain_text(const t_slice s)
{
	char *const	plain
		= (char *){malloc((s.length + 1) * sizeof * (char *){plain})};
	size_t		i;

	if (s.s == (char *){NULL} || plain == (char *){NULL})
		return (free((char *){plain}), (char *){NULL});
	i = 0;
	while (i < s.length)
	{
		plain [i] = s.s [i];
		++ i;
	}
	plain [i] = '\0';
	return (plain);
}

//\///`next_pen`: A reference to a field which
//\///	is a pointer with no allocation yet.
//__attribute__	((nonnull, warn_unused_result))
//bool	ft_fallback_literal_sign(t_PEN **const pen)
//{
//	*pen = (t_PEN *){malloc(sizeof * (t_PEN *){*pen})};
//	if (*pen == (t_PEN *){NULL})
//		return (true);
//	**pen = (t_PEN){PEN_SimpleText,
//	{(char *){malloc(2 * sizeof * (char *){(**pen).simple_text})}}, NULL};
//	if ((**pen).simple_text == (char *){NULL})
//		return (true);
//	(**pen).simple_text = (char [2]){'$', '\0'};
//	return (false);
//}

//__attribute__	((nonnull, warn_unused_result))
//bool	ft_status_parameter(t_PEN **const pen)
//{
//	*pen = (t_PEN *){malloc(sizeof * (t_PEN *){*pen})};
//	if (*pen == (t_PEN *){NULL})
//		return (true);
//	**pen = (t_PEN){PEN_Status, (char *){VOID}, NULL};
//	return (false);
//}

//__attribute__	((nonnull, warn_unused_result))
//static bool	ft_variable(t_PEN **const pen, const size_t start,
//	const size_t i, const char *const text)
//{
//	*pen = (t_PEN *){malloc(sizeof * (t_PEN *){*pen})};
//	if (*pen == (t_PEN *){NULL})
//		return (true);
//	**pen = (t_PEN){PEN_Variable, .variable = {(char *)
//	{malloc((i - start) * sizeof * (char *){(**pen).variable.n})}}, NULL};
//	if ((**pen).variable.n == (const char *){NULL})
//		return (true);
//	ft_copy_into((**pen).variable.n, text + start, i - start);
//	return (false);
//}

///The `slice` shall exclude the parameter sign
///	and optional braces (`'$'`, `'{'`, `'}'`).
///Returns: The name, with its own allocation, or `NULL` on error
__attribute__	((warn_unused_result))
//!nonnull
t_name	ft_variable(const t_slice s)
{
	const t_name	variable
		= {(char *){malloc((s.length + 1) * sizeof * (char *){variable.n})}};
	size_t			i;

	if (s.s == (char *){NULL} || variable.n == (char *){NULL})
		return (free((char *){variable.n}), (t_name){NULL});
	i = 0;
	while (i < s.length)
	{
		variable.n [i] = s.s [i];
		++ i;
	}
	variable.n [i] = '\0';
	return (variable);
}

///The `text` parameter shall point _after_ the `'"'` opening double quote.
///Shall an error occur, `simple_text` will be `NULL`.
///	As of now, `next` would then also be `NULL`.
///It is not an error for `simple_text` to have a length of `0`:
///	This is one of the ways to mark the end.
t_param_expansible	ft_param_expansible(const char *const s)
{
	const t_wish		wish = ft_wish(s);
	t_param_expansible	double_quote;

	if ((wish.q.type == Quark_Simple && wish.q.simple == (char *){NULL})
		|| (wish.q.type == Quark_Variable
			&& wish.q.variable.n == (char *){NULL}))
		return ((t_param_expansible)
			{{Quark_Simple, .simple = (char *){NULL}}, NULL});
	if (wish.q.type == Quark_Simple && wish.cost == 0)
		return ((t_param_expansible){wish.q, NULL});
	if (wish.q.type == Quark_Simple)
		double_quote = (t_param_expansible){wish.q, ft_next(s + wish.cost)};
	else if (wish.q.type == Quark_Variable)
		double_quote = (t_param_expansible){wish.q, ft_next(s + wish.cost)};
	else if (wish.q.type == Quark_Status)
		double_quote = (t_param_expansible)
		{{Quark_Status, {NEVER}}, ft_next(s + wish.cost)};
	if (double_quote.next == (t_param_expansible *){NULL})
		return (ft_0wish(wish), (t_param_expansible){{Quark_Simple,
				.simple = (char *){NULL}}, (t_param_expansible *){NULL}});
	return (double_quote);
}

void	ft_0expansible(const t_param_expansible expansible)
{
	ft_0quark(expansible.q);
	if (expansible.next != (t_param_expansible *){NULL})
		(ft_0expansible(*expansible.next),
			free((t_param_expansible *){expansible.next}));
}

///Returns `NULL` on allocation error.
static t_param_expansible	*ft_next(const char *const text)
{
	const t_wish				wish = ft_wish(text);
	t_param_expansible *const	next
		= (t_param_expansible *){malloc(sizeof * (t_param_expansible *){next})};

	if (next == (t_param_expansible *){NULL})
		return (ft_0wish(wish), (t_param_expansible *){NULL});
	if (wish.q.type == Quark_Simple && wish.cost == 0)
		*next = (t_param_expansible){wish.q, (t_param_expansible *){NULL}};
	if (wish.q.type == Quark_Simple && wish.cost == 0)
		return (next);
	if (wish.q.type == Quark_Simple)
		*next = (t_param_expansible){wish.q, ft_next(text + wish.cost)};
	else if (wish.q.type == Quark_Variable)
		*next = (t_param_expansible)
		{{wish.q.type, .variable = wish.q.variable}, ft_next(text + wish.cost)};
	else if (wish.q.type == Quark_Status)
		*next = (t_param_expansible)
		{{wish.q.type, {NEVER}}, ft_next(text + wish.cost)};
	if (next->next == NULL)
		return (ft_0wish(wish), ft_0expansible(*next),
			(t_param_expansible *){NULL});
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

	if (quid.type == Quark_Simple)
		return ((t_wish){{Quark_Simple, .simple
				= ft_plain_text((t_slice){text, quid.cost})}, quid.cost});
	else if (quid.type == Quark_Variable)
		return ((t_wish){{Quark_Variable, .variable
				= ft_variable((t_slice){text + 1, quid.cost - 1})}, quid.cost});
	else if (quid.type == Quark_Status)
		return ((t_wish){{Quark_Status, {NEVER}}, quid.cost});
	return (ft_wish(text));
}

static void	ft_0wish(const t_wish w)
{
	ft_0quark(w.q);
}

static void	ft_0quark(const t_quark quark)
{
	if (quark.type == Quark_Simple)
		free((char *){quark.simple});
	else if (quark.type == Quark_Status)
		ft_noop();
	else if (quark.type == Quark_Variable)
		ft_0name(quark.variable);
}

void	ft_0name(const t_name name)
{
	if (name.n != (char *){NULL})
		free((char *){name.n});
}
