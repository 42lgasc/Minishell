/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:00:19 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 21:21:15 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_QUOTE_H
# define DOUBLE_QUOTE_H

# include "quark.h"
# include "miscellaneous.h"

///Word Splitting only occurs where parameters are expund outside of quotes;
///	It is not the concern of non-parameter text and expansions within quotes.
///`Quark_Status` has no visible value in
///	the `union` as it is a unitary marker.
///`simple_text` may be empty ({'\0'}) and thus have a `cost` of `0`.
///`simple_text` and `variable` will be `NULL` on error.
typedef struct s_expansible
{
	t_quark				q;
	struct s_expansible	*next;
}	t_param_expansible;
typedef t_param_expansible	t_prmxpn;

t_prmxpn	ft_double_quote(const char *text)
			__attribute__	((nonnull,	warn_unused_result));
t_prmxpn	ft_param_expansible(const char *s)
			__attribute__	((nonnull,	warn_unused_result));
void		ft_free_expansible(t_param_expansible expansible);
void		ft_free_name(t_name name);
#endif
