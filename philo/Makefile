# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 18:27:43 by sclam             #+#    #+#              #
#    Updated: 2022/03/04 20:39:57 by sclam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	srcs/list_manipulation.c \
			srcs/inits.c \
			srcs/philo_threads.c \
			srcs/watcher_thread.c \
			srcs/utils.c \
			srcs/main.c

NAME	=	philo

CC		=	cc

OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

HEAD	=	includes/philo.h

%.o : %.c	${HEAD}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

bonus:		
			make -C ../philo_bonus
			cp -rf ../philo_bonus/philo_bonus philo_bonus

clean:
			${RM} ${OBJS}
			make clean -C ../philo_bonus

fclean:		
			${RM} ${OBJS}
			${RM} ${NAME}
			${RM} philo_bonus
			make fclean -C ../philo_bonus

re:			fclean all

.PHONY:		all clean fclean re
