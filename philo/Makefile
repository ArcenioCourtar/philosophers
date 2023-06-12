# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 16:57:57 by acourtar          #+#    #+#              #
#    Updated: 2023/06/12 15:55:06 by acourtar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
NAME		= philo
CFLAGS		= # -Wall -Werror -Wextra
SRCFILES	= main.c
			
HEADERFILES	= $(DIR_INC)philo.h

DIR_SRC		= src/
DIR_OBJ		= obj/
DIR_INC		= include/

ALL_OBJ		= $(addprefix $(DIR_OBJ), $(SRCFILES:.c=.o))
ALL_SRC		= $(addprefix $(DIR_SRC), $(SRCFILES))

#----------------------------------------------------------------------------

all: $(NAME)

$(NAME): $(ALL_OBJ)
	$(CC) $(CFLAGS) $(ALL_OBJ) -pthread -o $(NAME)

re: fclean all

clean:
	rm -rf $(DIR_OBJ)
	
fclean:
	rm -rf $(DIR_OBJ) philo

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(HEADERFILES)
	@mkdir -p $(DIR_OBJ)
	$(CC) -c -g $(CFLAGS) -pthread -o $@ $<

.PHONY: clean fclean re all