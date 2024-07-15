/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:00:19 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/15 17:02:30 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_QUOTE_H
# define DOUBLE_QUOTE_H

# define	CAPITAL		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define	SMALL		"abcdefghijklmnopqrstuvwxyz"
# define	NO_PLAIN	"\"$'"
// As the `bash` manual states.
// XXX: There is yet a requirement to not support some of such characters.
# define	META		" \t\n|<>"	//" \t\n|&;()<>"

# include "quark.h"

bool				ft_is_at_end(size_t start, size_t i, const char *text);
t_quid				ft_quark_id(const char *text);
//bool				ft_simple_text(
//						t_PEN **pen, size_t start, size_t i, const char *text);
char				*ft_plain_text(t_slice slice);
//bool				ft_status_parameter(t_PEN **pen);
//bool				ft_fallback_literal_sign(t_PEN **pen);
//bool				ft_variable(
//						t_PEN **pen, size_t start, size_t i, const char *text);
t_name				ft_variable(t_slice name);
t_param_expansible	ft_param_expansible(t_wish wish);
#endif
