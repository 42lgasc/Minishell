/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:26:59 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 22:01:19 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISCELLANEOUS_H
# define MISCELLANEOUS_H

///A BLank, as the `bash` manual states.
# define BLANK			" \t"
# define DIGIT			"0123456789"
# define CAPITAL			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define SMALL			"abcdefghijklmnopqrstuvwxyz"
# define NO_PLAIN		"\"$'"
///A Metacharacter, as the `bash` manual states.
///XXX: There is yet a requirement to not support some of such characters.
# define METACHARACTER	" \t\n|<>"	//" \t\n|&;()<>"

char	*ft_single_quote(const char *text)
		__attribute__	((nonnull,	warn_unused_result));
size_t	ft_plain_cost(const char *s)
		__attribute__	((	nonnull	,	warn_unused_result	));

typedef struct s_slice
{
	const char *const	s;
	const size_t		length;
}	t_slice;

char	*ft_plain_text(t_slice s)	__attribute__	((warn_unused_result));
		//!nonnull

///According to the Bash manual, section 2 Definitions:
///>A  `word`  consisting  solely  of  letters,  numbers,  and  underscores, and
///>beginning   with  a  letter  or  underscore.   `Name`s  are  used  as  shell
///>variable  and  function  names.   Also  referred  to  as  an   `identifier`.
///	In RegEx form: [A-Z_a-z][0-9A-Z_a-z]*
typedef union u_name
{
	char	*n;
}	t_name;
void	ft_free_name(t_name name);

t_name	ft_variable(const t_slice s)	__attribute__	((warn_unused_result));
		//!nonnull
#endif
