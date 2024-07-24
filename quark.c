/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quark.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:04:40 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 21:23:54 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "quark.h"

///The `text` parameter shall point _after_ the `'"'` opening double quote.
///On error, `simple_text` and `variable` will be `NULL`.
///It is no error for `simple_text` to have a length of `0`.
///TODO: Separate: There should be different functions for
///	identifying type, counting cost, and assembling the structure.
__attribute__	((nonnull,	warn_unused_result))
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

void	ft_free_wish(const t_wish w)
{
	ft_free_quark(w.q);
}

///The `text` parameter shall point _after_ the opening `'"'` double quote.
///The `cost` is the amount of characters which represents
///	a quark; The amount of meaningful characters may
///	be lesser due to affix markers such as `'$'`.
///A `Quark_SimpleText` may have a cost of `0`: This
///	means there are no more characters. Quarks of other
///	type may be last, but only this one can have no cost.
__attribute__	((nonnull,	warn_unused_result))
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

///Returns: A strind (with maybe zero length), or `NULL` on allocation error
__attribute__	((warn_unused_result))	//!nonnull
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

void	ft_free_quark(const t_quark quark)
{
	if (quark.type == Quark_Simple)
		free((char *){quark.simple});
	else if (quark.type == Quark_Status)
		ft_noop();
	else if (quark.type == Quark_Variable)
		ft_free_name(quark.variable);
}
