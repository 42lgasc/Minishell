/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quark.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:57:43 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 22:01:54 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUARK_H
# define QUARK_H

# include <stddef.h>

# include "miscellaneous.h"

///Explicit discard with `VOID`:
///	Use of `NULL` may indicate a field as incomplete, as awaiting for a value.
///	`NEVER` marks a field as "complete" - such pointer shall have no use.
///	`DIRT` acts as an _explicit_ placeholder value. Dirty!
# define NEVER	0

///>>How do Quarks hold together?
///>I know not.  Wishes, maybe?	~~lgasc 2024-07-03 17:22
enum e_quark
{
	Quark_Simple,
	Quark_Variable,
	Quark_Status
};
typedef struct s_quark
{
	enum e_quark	type;
	union
	{
		char	*simple;
		t_name	variable;
	};
}	t_quark;
void	ft_free_quark(t_quark quark);

///`StatusParameter` has no visible value in
///	the `union` as it is a unitary marker.
///`simple_text` may be the empty string ({'\0'}) and thus have a `cost` of `0`.
///	Freeing it is still necessary!
///`simple_text` and `variable` will be `NULL` on error.
typedef struct s_wish
{
	const t_quark	q;
	size_t			cost;
}				t_wish;
t_wish	ft_wish(const char *const text)
		__attribute__	((nonnull,	warn_unused_result));
void	ft_free_wish(const t_wish w);

typedef struct s_quark_id
{
	enum e_quark	type;
	size_t			cost;
}	t_quid;
t_quid	ft_quark_id(const char *text)
		__attribute__	((nonnull,	warn_unused_result));
#endif
