NAME_B		=	philo_bonus

HEADER_B	=	philo_bonus.h

SRCS_B		=	main.c	philos_simulation.c		check_end.c		philo_bonus_utils.c		ft_atoi.c	ft_usleep.c

OBJS_B		=	$(SRCS_B:%.c=%.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

.PHONY		=	all	clean fclean re

all:			$(NAME_B)

$(NAME_B):		$(OBJS_B) $(HEADER_B)
				$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME_B)

%.o:			%.c $(HEADER_B)
				$(CC) $(CFLAGS) -c $< -o $@

clean:			
				rm -f $(OBJS_B)

fclean:			clean
				rm -f $(NAME_B)

re:				fclean all