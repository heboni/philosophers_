NAME_B		=	philo_bonus

HEADER_B	=	philo_bonus.h

SRCS_B		=	main.c	ft_atoi.c

OBJS_B		=	$(SRCS_B:%.c=%.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

.PHONY		=	all	clean fclean re

all:			$(NAME)

$(NAME):

clean:

fclean:			clean
				rm

re:				fclean all