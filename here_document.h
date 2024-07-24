/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:49:17 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 20:59:41 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOCUMENT_H
# define HERE_DOCUMENT_H

# include "stddef.h"

size_t		ft_here_word_length(const char *s)
			__attribute__	((nonnull,	warn_unused_result));

//enum e_here_word
//{
//};
//typedef const struct s_here_word
//{
//	const enum e_here_word	type;
//	const union
//	{
//		
//	};
//}	t_here_word;

///XXX: Single quotes and double quotes behave identically there.
///	Or don't they?	~~lgasc 2024-06-13 17:39
enum e_here_document
{
	HereDocument_Quoteless,
	HereDocument_Quotesome
};
///No need to store the closing delimiter.
///The `word` of the `Quotesome` type is the aftermath of Quote Removal.
///	Remember, Quote Removal also apply the `\` Escape
///		Character and "glue quotes" (such as in `AB'CD'EF`
///		and `''ABC''DEF''`, both equivalent to `ABCDEF`).
///	TODO: Should the word of `<<''` have for representation
///		a `NULL` pointer or an `&'\0'` empty string?
typedef struct s_here_document
{
	enum e_here_document	type;
	char					*word;
}	t_here_document;
typedef t_here_document		t_heredc;

t_heredc	ft_here_document(const char *text)
			__attribute__	((nonnull,	warn_unused_result));
void		ft_free_heredoc(t_here_document h);
#endif
