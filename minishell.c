/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgasc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:56:14 by lgasc             #+#    #+#             */
/*   Updated: 2024/07/18 03:21:08 by lgasc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "parsing.h"

#define NAME	"minishell"
//#define PS1	"\s-\v\$"
//#define PS1	(argv [0] "-" MINISHELL_VERSION IF_ROOT)
//#define PS1	NAME "-0#$"
#define PS1		"minishell-0? "

// TODO: register signal handlers;
// What does `rl_replace_line(PS1, 0);` do?
//https://tiswww.cwru.edu/php/chet/readline/rltop.html#Documentation
//\//parse = ft_parse(line);
//\//if (parse is partial)
//\//	read some more;
// 3.1.1 Shell Operation
//(ft_break__obeing_quoting__sep_token_by_metachar__alias_expansion
//\	(line), ft_parse_tokens_into_commands(),
//\	ft_shell_expansion__filename_expansion_and_commands_and_arguments(),
//\	ft_redirect__rm_redirection_operator_from_arg_list(), ft_execute(),
//\	ft_optionally_wait_completion__collect_exit_status());
int	main(void)
{
	const char	*line;
	t_parse		parse;

	while (1)
	{
		line = readline(PS1);
		if (line != NULL && line [0] != '\0')
			add_history(line);
		parse = ft_parse(line);
		free((char *)(const char *){line});
		ft_free_parse(parse);
	}
}

/*static void ft_break__obeing_quoting__sep_token_by_metachar__alias_expansion
	(const char *const line)
{
	size_t	i;
	

	if (line == NULL)
		return ;
	i = 0;
	while (line [i] != '\0')
		;
	// FIXME: Group together `quote == None` conditions.
	//if (quote == None && line [i] == '\\')
	//	quote = Escape;
	//else if (quote == Escape)
	//	if (line [i] == '\n')
	//		quote = (ft_line_continuation(), None);
	//	else
	//		quote = (ft_preserve(), None);
	else if (quote == None && line [i] = '\'')
		quote = Single;
	else if (quote == Single)
		if (line [i] == '\'')
			quote = None;
		else
			ft_preserve();
	else if (quote == None && line [i] == '\"')
		quote = Double;
	else if (quote == Double)
		if (line [i] == '$')
			quote == DoubleParameter; // TODO: SEE: Shell Expansions
		//else if (line [i] == '`' '\\' '!')
		else if (line [i] == '"')
			quote == None;
		else
			ft_preserve();
	else
		ft_handle_unquoted();
}*/

/*static void	f_parse(void)
{
	const enum e_atom	quote_here;
	const enum e_atom	last_atom;

	//...
	
	//if (quote_here == NoQuote)
	if (quote_here == SingleQuote || quote_here == DoubleQuote
		|| last_atom == InputRedirection || last_atom == OutputRedirection
		|| quote_here == HereDocument && not (
			//Here Document end
			) || last_atom == AppendingRedirection || last_atom == Pipe)
		return (partial_parse); // More line reading required...
}*/
