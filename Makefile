# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/30 17:00:00 by ssoukoun          #+#    #+#              #
#    Updated: 2025/04/30 17:01:18 by ssoukoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/02 16:48:52 by ssoukoun          #+#    #+#              #
#    Updated: 2025/02/04 16:23:10 by fsingh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
HEAD = .
CFLAGS = -g3 -Wall -Werror -Wextra
SOURCES = main.c routine.c init.c utils.c 

OBJECTS = $(SOURCES:.c=.o)  # Génération des fichiers .o automatiquement

all: $(NAME) 

$(NAME): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) ${LIBFT_A} -g -o $(NAME) $(LDFLAGS)  

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEAD)  # Compilation des .c en .o

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re 
