# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleseur <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 14:34:54 by rleseur           #+#    #+#              #
#    Updated: 2022/03/22 14:16:09 by rleseur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####### DESIGN #######

# Style de typo :
_FIN			=	\033[0m
_GRAS			=	\033[1m
_ITA			=	\033[3m
_SOUS			=	\033[4m
_CLIGN			=	\033[5m
_REV			=	\033[7m

# Couleurs des lettres :
_GRIS			=	\033[30m
_ROUGE			=	\033[31m
_VERT			=	\033[32m
_JAUNE			=	\033[33m
_BLEU			=	\033[34m
_VIOLET			=	\033[35m
_CYAN			=	\033[36m
_BLANC			=	\033[37m

# Couleurs de fonds :
_IGRIS			=	\033[40m
_IROUGE			=	\033[41m
_IVERT			=	\033[42m
_IJAUNE			=	\033[43m
_IBLEU			=	\033[44m
_IVIOLET		=	\033[45m
_ICYAN			=	\033[46m
_IBLANC			=	\033[47m

# Appel
_VALID			=	/bin/echo -e "${_JAUNE}\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\n\
					${_VERT}${_IVIOLET}\#\# $1${_FIN}"
_EMOJI			=	/bin/echo -e "${_GRAS}${_VIOLET}$1${_FIN}\n"

CREATED_BIN		=	@$(call _VALID,"Binary created!")
CREATED_LIBFT	=	@$(call _VALID,"Libft library created!")
DELETED_OBJS	=	@$(call _VALID,"Objs deleted!")
DELETED_BIN		=	@$(call _VALID,"Binary deleted!")


####### MAKEFILE #######

### Variables

SRCS_PATH		=	./srcs/
OBJS_PATH		=	./objs/
FILES			=	main.c			\
					philo.c			\
					messages.c		\
					utils.c			\
					check_args.c	\
					errors.c
SRCS			=	${addprefix ${SRCS_PATH}, ${FILES}}
OBJS			=	${addprefix ${OBJS_PATH}, ${FILES:.c=.o}}

HEADER_PATH		=	./headers/
HEADER			=	${HEADER_PATH}philosophers.h

NAME			=	philosophers

CC				=	clang
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror #-fsanitize=thread -g3

### Commandes

all:			${NAME}

${NAME}:		${OBJS}
				${CC} ${CFLAGS} -lpthread ${OBJS} -o ${NAME}
				${CREATED_BIN}

${OBJS_PATH}%.o:	${SRCS_PATH}%.c
				mkdir -p ${dir $@}
				${CC} -c ${CFLAGS} -I${HEADER_PATH} $^ -o $@

clean:
				${RM} ${OBJS_PATH}
				${DELETED_OBJS}

fclean:			clean
				${RM} ${NAME}
				${DELETED_BIN}

re:				fclean all

.PHONY:			all clean fclean re
