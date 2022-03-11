# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 18:27:43 by sclam             #+#    #+#              #
#    Updated: 2021/12/12 20:25:31 by sclam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	srcs/list_manipulation_bonus.c \
			srcs/inits_bonus.c \
			srcs/philo_processes_bonus.c \
			srcs/processes_bonus.c \
			srcs/watcher_bonus.c \
			srcs/utils_bonus.c \
			srcs/main_bonus.c

NAME	=	philo_bonus

CC		=	cc

OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

HEAD	=	includes/philo_bonus.h

%.o : %.c	${HEAD}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		
			${RM} ${OBJS}
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re