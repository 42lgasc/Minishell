/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:15:29 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/24 20:41:22 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLE_H
# define PARTICLE_H

# include <stdbool.h>

# include "double_quote.h"

enum e_particle
{
	Particle_Plain,
	Particle_SingleQuote,
	Particle_DoubleQuote,
	Particle_Variable,
	Particle_StatusParameter,
};
typedef struct s_particle
{
	enum e_particle	type;
	union
	{
		char				*plain;
		char				*single_quote;
		t_param_expansible	double_quote;
		t_name				variable;
	};
}				t_particle;
typedef t_particle			t_ptcl;
typedef struct s_particle_node
{
	t_particle				p;
	struct s_particle_node	*next;
}	t_particle_node;
typedef t_particle_node		t_ptclnd;

t_ptclnd	ft_particle_node(const char *text)
			__attribute__	((nonnull,	warn_unused_result));
void		ft_free_particle_node(t_particle_node n);
t_ptcl		ft_particle(const char *s)
			__attribute__	((nonnull,	warn_unused_result));
void		ft_free_particle(t_particle p);
size_t		ft_particle_cost(const char *s)
			__attribute__	((nonnull,	warn_unused_result));
#endif
