/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quark.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:57:43 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/18 06:01:28 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUARK_H
# define QUARK_H

# include <stddef.h>

///Explicit discard with `VOID`:
///	Use of `NULL` may indicate a field as incomplete, as awaiting for a value.
///	`NEVER` marks a field as "complete" - such pointer shall have no use.
///	`DIRT` acts as an _explicit_ placeholder value. Dirty!
# define NEVER	NULL
# define VOID	NEVER	//!Depreciated: Rename to `NEVER`.
# define IVOID	-1		//!Depreciated; maybe use `(int)VOID`?
# define DIRT	NULL	//!Depreciated

///According to the Bash manual, section 2 Definitions:
///>A  `word`  consisting  solely  of  letters,  numbers,  and  underscores, and
///>beginning   with  a  letter  or  underscore.   `Name`s  are  used  as  shell
///>variable  and  function  names.   Also  referred  to  as  an   `identifier`.
///	In RegEx form: [A-Z_a-z][0-9A-Z_a-z]*
typedef union u_name
{
	char	*n;
}	t_name;
void	ft_0name(t_name name);

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
typedef struct s_spring
{
	const t_param_expansible	expansible;
	const size_t				cost;
}	t_spring	__attribute__	((deprecated));

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
		__attribute__	((nonnull, warn_unused_result));

typedef struct s_quark_id
{
	enum e_quark	type;
	size_t			cost;
}	t_quid;

typedef struct s_slice
{
	const char *const	s;
	const size_t		length;
}	t_slice;
#endif
