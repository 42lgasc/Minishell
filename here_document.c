/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:51:17 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 20:59:22 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "miscellaneous.h"

#include "here_document.h"

///The `delimiter` may be the empty string. (It then matches an empty line.)
///For the scope of this `minishell` project, there
///	is no support for the `'\\'` Escape Character.
///Returns `NULL` on allocation error.
__attribute__	((nonnull,	warn_unused_result))
t_here_document	ft_here_document(const char *const text)
{
	char *const				word = (char *)
	{malloc((ft_here_word_length(text) + 1) * sizeof * (char *){word})};
	enum e_here_document	quote;
	const char				*ti;
	char					*wi;

	if (word == (char *){NULL})
		return ((t_heredc){-1, NULL});
	quote = HereDocument_Quoteless;
	ti = text;
	wi = word;
	while (*ti != '\0' && ! ft_strchr(METACHARACTER, *ti))
		if (quote == HereDocument_Quoteless && (*ti == '"' || *ti == '\''))
			quote = HereDocument_Quotesome;
	else if (*ti == '"')
		while (*++ ti != '\0' && (*ti != '"' || (++ ti, false)))
			*wi ++ = *ti;
	else if (*ti == '\'')
		while (*++ ti != '\0' && (*ti != '\'' || (++ ti, false)))
			*wi ++ = *ti;
	else
		while (*ti != '\0' && ! ft_strchr("\"'" METACHARACTER, *ti))
			*wi ++ = *ti ++;
	*wi = '\0';
	return ((t_heredc){quote, word});
}

void	ft_free_heredoc(t_here_document h)
{
	if (h.word != (char *){NULL})
		free((char *){h.word});
}

__attribute__	((nonnull,	warn_unused_result))
size_t	ft_here_word_length(const char *const s)
{
	size_t		length;
	const char	*si;

	length = 0;
	si = s;
	while (*si != '\0' && ! ft_strchr("\"'" METACHARACTER, *si))
		if (*si == '"')
			while (*++ si != '\0' && (*si != '"' || (++ si, false)))
				++ length;
	else if (*si == '\'')
		while (*++ si != '\0' && (*si != '\'' || (++ si, false)))
			++ length;
	else
		while (*si != '\0' && ! ft_strchr("\"'" METACHARACTER, *si))
			length += (++ si, 1);
	return (length);
}
