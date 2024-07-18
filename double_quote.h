/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:00:19 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/17 21:56:03 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_QUOTE_H
# define DOUBLE_QUOTE_H

# include "quark.h"

bool		ft_is_at_end(size_t start, size_t i, const char *text);
t_quid		ft_quark_id(const char *text);
//bool		ft_simple_text(t_PEN**pen, size_t start, size_t i, const char*text);
char		*ft_plain_text(t_slice slice);
//bool		ft_status_parameter(t_PEN **pen);
//bool		ft_fallback_literal_sign(t_PEN **pen);
//bool		ft_variable(t_PEN **pen, size_t start, size_t i, const char *text);
t_name		ft_variable(t_slice name);
t_prmxpn	ft_param_expansible(const char *s);
void		ft_0expansible(t_param_expansible expansible);
#endif
