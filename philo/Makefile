NAME	=	philo

HEADER	= 	philo.h

SRCS	=	main.c	philo.c		check_end.c		philo_utils.c	init_utils.c	free_utils.c	ft_atoi.c	ft_usleep.c

OBJS	=	${SRCS:%.c=%.o}

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

.PHONY:		all clean fclean re


all:		${NAME}

${NAME}:	${OBJS} ${HEADER}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}


%.o:		%.c ${HEADER}
			${CC} ${CFLAGS} -c $< -o $@

clean:		
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all