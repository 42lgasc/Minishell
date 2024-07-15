# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgasc <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 18:19:19 by lgasc             #+#    #+#              #
#    Updated: 2024/07/14 21:11:27 by lgasc            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SOURCES	= $(NAME).c parsing.c #double_quote.c

LIBFT	= 

OBJECTS	= $(SOURCES:.c=.o) $(LIB_ARCHIVES)


CFLAGS	+= -Wmissing-noreturn -Werror -Wpedantic	\
	-Wnull-dereference -Wstrict-overflow=5 -Wall	\
	-Wattributes -Wmissing-format-attribute			\
	-Wextra #-Wsuggest-attribute=returns_nonnull
ifeq ($(CC), gcc)
CFLAGS += -Wduplicated-cond -Wsuggest-attribute=const	\
	-Wsuggest-attribute=cold -Wsuggest-attribute=pure	\
	-Wduplicated-branches -Wsuggest-attribute=format	\
	-Wattribute-alias=2 -Wsuggest-attribute=noreturn	\
	-Wsuggest-attribute=malloc -Wstringop-overflow=4
else ifeq ($(CC), clang)
CFLAGS += -Wproperty-attribute-mismatch
endif

LDLIBS	+= -lreadline



.PHONY:	all re clean fclean	debug test

$(NAME):	$(OBJECTS)
	-grep 'TODO\|FIXME\|XXX\|?\|!!\|DEPREC\w*\|[Dd]eprec\w*' -r .

all:		$(NAME)

clean:		
	for O in $(OBJECTS);	\
		do if [ -f $$O ];		\
			then rm $$O;		\
			fi done

fclean:		clean
	if [ -f $(NAME) ];		\
		then rm $(NAME);	\
		fi

re:			fclean all



# Use `CC=...` instead.
#test:		$(OBJECTS)
#	- clang	$(CFLAGS) $(OBJECTS) $(LDLIBS)
#	- gcc	$(CFLAGS) $(OBJECTS) $(LDLIBS)
#	$(CC)	$(CFLAGS) $(OBJECTS) $(LDLIBS)



#$(SOURCES:.c=.o):	$@
#	echo '@$@ <$< ?$? ^$^'
