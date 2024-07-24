/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:59:45 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 22:01:40 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdbool.h>

#include "libft/libft.h"

#include "double_quote.h"

static t_prmxpn	*ft_next(const char *const text)
				__attribute__	((nonnull,	warn_unused_result));

///The `text` parameter shall point _after_ the `'"'` opening double quote.
///As a mean of error propagation, `expansible.simple_text`
///	and `expansible.variable` may be `NULL`.
///TODO: Separate: There should be a separate function to count the cost.
__attribute__	((nonnull,	warn_unused_result))
t_param_expansible	ft_double_quote(const char *const text)
{
	const t_param_expansible		double_quote = ft_param_expansible(text);

	return (double_quote);
}

///The `text` parameter shall point _after_ the `'"'` opening double quote.
///Shall an error occur, `simple_text` will be `NULL`.
///	As of now, `next` would then also be `NULL`.
///It is not an error for `simple_text` to have a length of `0`:
///	This is one of the ways to mark the end.
__attribute__	((nonnull,	warn_unused_result))
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
		return (ft_free_wish(wish), (t_param_expansible){{Quark_Simple,
				.simple = (char *){NULL}}, (t_param_expansible *){NULL}});
	return (double_quote);
}

void	ft_free_expansible(const t_param_expansible expansible)
{
	ft_free_quark(expansible.q);
	if (expansible.next != (t_param_expansible *){NULL})
		(ft_free_expansible(*expansible.next),
			free((t_param_expansible *){expansible.next}));
}

void	ft_free_name(const t_name name)
{
	if (name.n != (char *){NULL})
		free((char *){name.n});
}

///Returns `NULL` on allocation error.
static t_param_expansible	*ft_next(const char *const text)
{
	const t_wish				wish = ft_wish(text);
	t_param_expansible *const	next
		= (t_param_expansible *){malloc(sizeof * (t_param_expansible *){next})};

	if (next == (t_param_expansible *){NULL})
		return (ft_free_wish(wish), (t_param_expansible *){NULL});
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
		return (ft_free_wish(wish), ft_free_expansible(*next),
			(t_param_expansible *){NULL});
	return (next);
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
