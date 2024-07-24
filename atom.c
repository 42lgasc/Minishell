/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:28:21 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 20:54:12 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "double_quote.h"

#include "atom.h"

static t_atom	ft_rectify(t_atom a)	__attribute__	((warn_unused_result));
static t_atom	ft_error_atom(void)	__attribute__	((warn_unused_result));

///The `text` parameter shall point to the
///	first (non-blank) character of the atom.
///The `field.p.plain_text` shall be `NULL` on allocation error,
///	regardless of the expectations on the atom `type`.
__attribute__	((nonnull,	warn_unused_result))
t_atom	ft_atom(const char *const s)
{
	t_atom	a;

	if (*s == '|')
		return ((t_atom)
			{Atom_Pipe, {{{Particle_Plain, {NEVER}}, (t_ptclnd *){NULL}}}});
	else if (*s == '<' && s [1] == '<')
		a = ft_rectify((t_atom){Atom_HereDocument, .here_document
				= ft_here_document(s + 2 + ft_span(s + 2, BLANK))});
	else if (*s == '<')
		a = ft_rectify((t_atom){Atom_Input,
				.input = ft_particle_node(s + 1 + ft_span(s + 1, BLANK))});
	else if (*s == '>' && s [1] == '>')
		a = ft_rectify((t_atom){Atom_Appending,
				.appending = ft_particle_node(s + 2 + ft_span(s + 2, BLANK))});
	else if (*s == '>')
		a = ft_rectify((t_atom){Atom_Output,
				.output = ft_particle_node(s + 1 + ft_span(s + 1, BLANK))});
	else
		a = (t_atom){Atom_Field, .field = ft_particle_node(s)};
	return (a);
}

void	ft_free_atom(const t_atom a)
{
	if (a.type == Atom_Field)
		ft_free_particle_node(a.field);
	else if (a.type == Atom_Input)
		ft_free_particle_node(a.input);
	else if (a.type == Atom_Output)
		ft_free_particle_node(a.output);
	else if (a.type == Atom_Appending)
		ft_free_particle_node(a.appending);
	else if (a.type == Atom_HereDocument)
		ft_free_heredoc(a.here_document);
}

static t_atom	ft_rectify(const t_atom a)
{
	if ((a.type == Atom_HereDocument && a.here_document.word == (char *){NULL})
		|| (a.type == Atom_Input && a.input.p.type == Particle_Plain
			&& a.input.p.plain == (char *){NULL})
		|| (a.type == Atom_Appending && a.appending.p.type == Particle_Plain
			&& a.appending.p.plain == (char *){NULL})
		|| (a.type == Atom_Output && a.output.p.type == Particle_Plain
			&& a.output.p.plain == (char *){NULL}))
		return (ft_free_atom(a), ft_error_atom());
	return (a);
}

static t_atom	ft_error_atom(void)
{
	return ((t_atom){Atom_Field, .field
		= {{Particle_Plain, .plain = (char *){NULL}}, (t_ptclnd *){NULL}}});
}
