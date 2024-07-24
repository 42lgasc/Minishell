/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:26:03 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 22:02:07 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "atom.h"

typedef struct s_bond
{
	t_atom			a;
	struct s_bond	*next;
}				t_parse;
t_parse	ft_parse(const char *text)__attribute__ ((nonnull, warn_unused_result));
void	ft_free_parse(t_parse p);
#endif
