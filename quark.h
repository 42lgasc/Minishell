/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quark.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:57:43 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/14 22:00:22 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUARK_H
# define QUARK_H

///According to the Bash manual, section 2 Definitions:
///>A  `word`  consisting  solely  of  letters,  numbers,  and  underscores, and
///>beginning   with  a  letter  or  underscore.   `Name`s  are  used  as  shell
///>variable  and  function  names.   Also  referred  to  as  an   `identifier`.
///	In RegEx form: [A-Z_a-z][0-9A-Z_a-z]*
typedef union u_name
{
	char *const	n;
}	t_name;

///>How do Quarks hold together?
///	I know not.  Wishes, maybe?	~~lgasc 2024-07-03 17:22
enum e_quark
{
	Quark_SimpleText,
	Quark_Variable,
	Quark_Status
};
typedef struct s_quark_id
{
	enum e_quark	type;
	size_t			cost;
}	t_quid;
typedef const struct s_quark
{
	const enum e_quark	type;
	const union
	{
		const char *const	simple_text;
		const t_name		variable;
	};
}	t_quark;
///`StatusParameter` has no visible value in
///	the `union` as it is a unitary marker.
///`simple_text` may be the empty string ({'\0'}) and thus have a `cost` of `0`.
///	Freeing it is still necessary!
///`simple_text` and `variable` will be `NULL` on error.
typedef const struct s_wish
{
	const t_quark	quark;
	size_t			cost;
}				t_wish;

typedef struct s_slice
{
	const char *const	string;
	const size_t		length;
}	t_slice;
#endif
