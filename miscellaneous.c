/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:26:59 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/25 18:50:24 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "miscellaneous.h"

///The `text` parameter shall point right **after** the opening `'\''` quote.
///Returns `NULL` on allocation error.
__attribute__	((nonnull,	warn_unused_result))
char	*ft_single_quote(const char *const text)
{
	char *const	content = (char *)
	{malloc((ft_find(text, "'") + 1) * sizeof * (char *){content})};

	if (content == (char *){NULL})
		return ((char *){NULL});
	if (ft_strlcpy(content, text, ft_find(text, "'")) >= ft_find(text, "'"))
		ft_noop();
	return (content);
}

///For the scope of this `minishell` project, there
///	is no support for the `'\\'` Escape Character.
__attribute__	((nonnull,	warn_unused_result))
size_t	ft_plain_cost(const char *const s)
{
	return (ft_find(s, "\"$'" METACHARACTER));
}

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
