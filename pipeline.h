/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:58:27 by lgasc             #+#    #+#             */
/*   Updated: 2024/04/24 20:00:43 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "command.h"

typedef t_command	t_pipeline [];
typedef int			t_exit_status;

void			ft_create_pipeline(void);
t_exit_status	ft_execute_pipeline(t_pipeline pipeline);
#endif
