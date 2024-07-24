/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:42:43 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 20:42:33 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"

#include "atom.h"
#include "double_quote.h"
#include "miscellaneous.h"

#include "parsing.h"

static t_parse	ft_error_parse(void)	__attribute__	((warn_unused_result));
static size_t	ft_atom_cost(const char *const s)
				__attribute__	((nonnull,	warn_unused_result));
static size_t	ft_here_word_cost(const char *const s)
				__attribute__	((nonnull,	warn_unused_result));

///Shall `field.plain_text` be `NULL` on allocation error.
__attribute__	((nonnull,	warn_unused_result))
t_parse	ft_parse(const char *const s)
{
	t_parse *const	next = (t_parse *){malloc(sizeof * (t_parse *){next})};
	const char		*si;
	t_atom			a;

	si = s + ft_span(s, BLANK);
	if (*si == '\0')
		return (ft_error_parse());
	a = ft_atom(si);
	if (a.type == Atom_Field && a.field.p.type == Particle_Plain
		&& a.field.p.plain == (char *){NULL})
		return (ft_free_atom(a), ft_error_parse());
	si += ft_atom_cost(si) + ft_span(s, BLANK);
	if (*si == '\0')
		return ((t_parse){a, (t_parse *){NULL}});
	if (next == (t_parse *){NULL})
		return (ft_free_atom(a), ft_error_parse());
	*next = ft_parse(si);
	if (next->a.type == Atom_Field && next->a.field.p.type == Particle_Plain
		&& next->a.field.p.plain == (char *){NULL})
		return (ft_free_atom(a),
			ft_free_parse(*next), free((t_parse *){next}), ft_error_parse());
	return ((t_parse){a, next});
}

void	ft_free_parse(const t_parse p)
{
	ft_free_atom(p.a);
	if (p.next != (t_parse *){NULL})
		(ft_free_parse(*p.next), free((t_parse *){NULL}));
}

static t_parse	ft_error_parse(void)
{
	return ((t_parse){{Atom_Field, .field = {{Particle_Plain, .plain = (char *)
					{NULL}}, (t_ptclnd *){NULL}}}, (t_parse *){NULL}});
}

static size_t	ft_atom_cost(const char *const s)
{
	if (*s == '|')
		return (1);
	else if (*s == '<' && s [1] == '<')
		return (2 + ft_span(s + 2, BLANK) + (s [2 + ft_span(s + 2, BLANK)]
				!= '\0') * ft_here_word_cost(s + 2 + ft_span(s + 2, BLANK)));
	else if (*s == '>' && s [1] == '>')
		return (2 + ft_span(s + 2, BLANK)
			+ ft_particle_cost(s + 2 + ft_span(s + 1, BLANK)));
	else if (*s == '<' || *s == '>')
		return (1 + ft_span(s + 1, BLANK)
			+ ft_particle_cost(s + 1 + ft_span(s + 1, BLANK)));
	else
		return (ft_particle_cost(s));
}

static size_t	ft_here_word_cost(const char *const s)
{
	size_t	cost;

	cost = 0;
	while (s [cost] == '\0')
	{
		if (s [cost] == '\0')
			return (cost);
		else if (s [cost] == '"' && (++ cost, true))
			while (s [cost] != '\0' && (s [cost] != '"' || (++ cost, false)))
				++ cost;
		else if (s [cost] == '\'' && (++ cost, true))
			while (s [cost] != '\0' && (s [cost] != '\'' || (++ cost, false)))
				++ cost;
		else
		{
			cost += ft_find(s + cost, "\"'" METACHARACTER);
			if (ft_strchr(METACHARACTER, s [cost]))
				return (cost);
		}
	}
	return (cost);
}
