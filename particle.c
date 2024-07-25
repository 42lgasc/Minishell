/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:19:44 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/25 18:46:50 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "miscellaneous.h"

#include "particle.h"

///The `plain_text` shall be `NULL` on allocation error.
__attribute__	((nonnull,	warn_unused_result))
t_ptclnd	ft_particle_node(const char *const text)
{
	const t_particle		p = ft_particle(text);
	t_particle_node *const	next
		= (t_ptclnd *){malloc(sizeof * (t_ptclnd *){next})};

	if ((ft_strchr(METACHARACTER, text [ft_particle_cost(text)])
			&& next == (t_ptclnd *){NULL})
		|| (p.type == Particle_Plain && p.plain == (char *){NULL})
		|| (p.type == Particle_SingleQuote && p.single_quote == (char *){NULL})
		|| (p.type == Particle_DoubleQuote && p.double_quote.q.type
			== Quark_Simple && p.double_quote.q.simple == (char *){NULL})
		|| (p.type == Particle_Variable && p.variable.n == (char*){NULL}))
		return (ft_free_particle(p), free((t_ptclnd *){next}), (t_ptclnd){{
			Particle_Plain, .plain = (char *){NULL}}, (t_ptclnd *){NULL}});
	if (ft_strchr(METACHARACTER, text [ft_particle_cost(text)]))
		return ((t_ptclnd){p, (t_ptclnd *){NULL}});
	*next = ft_particle_node(text + ft_particle_cost(text));
	if (next->p.type == Particle_Plain && next->p.plain == (char *){NULL})
		return (ft_free_particle(p), ft_free_particle_node(*next),
			free((t_ptclnd *){next}), (t_ptclnd){{Particle_Plain,
			.plain = (char *){NULL}}, (t_ptclnd *){NULL}});
	return ((t_ptclnd){p, next});
}

void	ft_free_particle_node(const t_particle_node n)
{
	ft_free_particle(n.p);
	if (n.next != (t_particle_node *){NULL})
		(ft_free_particle_node(*n.next), free((t_particle_node *){n.next}));
}

///A `Particle_PlainText` may have a `cost` of 0, this is no error.
///	In this case, the `plain_text` shall be the `""` empty string literal.
///		Remember, you shall not `free` a string literal!
///TODO: `plain_text` should absorb surrounding non-parameter `'$'`;
///	this currently produce consecutive `plain_text` from
///	text such as `"abc$+de"` (`"abc"`, `"$"`, and `"de"`)
///	while the result should be a single `plain_text`.
__attribute__	((nonnull,	warn_unused_result))
//else // Also if `text [0] == '$' && text [1] != 'A-Z' | 'a-z' | '_'`
t_particle	ft_particle(const char *const text)
{
	if (text [0] == '\'')
		return ((t_particle){Particle_SingleQuote,
			.plain = ft_single_quote(text + 1), //1 + ft_find(text + 1, "'") + 1
		});
	else if (text [0] == '"')
		return ((t_particle){Particle_DoubleQuote, .double_quote
			= ft_double_quote(text + 1//, ft_find(text,"\"") + ?
			)});
	else if (text [0] == '$' && text [1] == '?')
		return ((t_particle){Particle_StatusParameter, {NEVER}});
	else if (text [0] == '$' && (ft_isalpha(text [1]) || text [1] == '_'))
		return (
			(t_particle){Particle_Variable, .variable = ft_variable((t_slice)
				{text + 1, 1 + ft_span(text + 2, DIGIT CAPITAL "_" SMALL)})});
	else if (text [0] == '\0'
		|| ft_strchr(METACHARACTER, text [0]) != (char *){NULL})
		return ((t_particle){Particle_Plain, .plain = ""});
	else
		return ((t_particle){Particle_Plain,
			.plain = ft_plain_text((t_slice){text, ft_plain_cost(text)})});
}

void	ft_free_particle(const t_particle p)
{
	if (p.type == Particle_Plain && p.plain != (char *){""})
		free((char *){p.plain});
	else if (p.type == Particle_SingleQuote && p.single_quote != (char *){""})
		free((char *){p.single_quote});
	else if (p.type == Particle_DoubleQuote)
		ft_free_expansible(p.double_quote);
	else if (p.type == Particle_Variable)
		ft_free_name(p.variable);
}

__attribute__	((nonnull,	warn_unused_result))
size_t	ft_particle_cost(const char *const s)
{
	if (*s == '\'')
		return (1 + ft_find(s + 1, "'") + 1);
	else if (*s == '"')
		return (1 + ft_find(s + 1, "\"") + 1);
	else if (*s == '$' && s [1] == '?')
		return (2);
	else if (*s == '$' && (s [1] == '_' || ft_isalpha(s [1])))
		return (1 + ft_span(s + 2, DIGIT CAPITAL "_" SMALL));
	else if (*s == '\0' || ft_strchr(METACHARACTER, *s))
		return (0);
	else
		return (ft_plain_cost(s));
}
//__attribute__ ((alias ("ft_find")))
//static size_t	ft__single_quote_cost();
