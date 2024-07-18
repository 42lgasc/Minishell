/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:26:03 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/18 03:41:19 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "atom.h"

t_parse	ft_parse(const char *text)__attribute__ ((nonnull, warn_unused_result));
void	ft_free_parse(t_parse p);
#endif
