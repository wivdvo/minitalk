# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 15:47:58 by wvan-der          #+#    #+#              #
#    Updated: 2023/11/03 16:14:07 by wvan-der         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = 				client
SERVER = 				server

CLIENT_SRCS = 			srcs/client.c
SERVER_SRCS = 			srcs/server.c

CLIENT_OBJS = 			$(CLIENT_SRCS:.c=.o)
SERVER_OBJS = 			$(SERVER_SRCS:.c=.o)

CLIENT_BONUS = 			client_bonus
SERVER_BONUS = 			server_bonus

CLIENT_SRCS_BONUS =		srcs_bonus/client_bonus.c
SERVER_SRCS_BONUS = 	srcs_bonus/server_bonus.c

CLIENT_OBJS_BONUS = 	$(CLIENT_SRCS_BONUS:.c=.o)
SERVER_OBJS_BONUS = 	$(SERVER_SRCS_BONUS:.c=.o)

CC = 					cc
CFLAGS = 				-Wall -Werror -Wextra
PRINTF = 				ft_printf/libftprintf.a
RM = 					rm -rf

all: 					$(CLIENT) $(SERVER)

$(PRINTF):
							make -C ft_printf

$(CLIENT): 				$(CLIENT_OBJS) $(PRINTF)
							$(CC) $(CFLAGS) $(CLIENT_OBJS) $(PRINTF) -o client
$(SERVER): 				$(SERVER_OBJS) $(PRINTF)
							$(CC) $(CFLAGS) $(SERVER_OBJS) $(PRINTF) -o server

$(CLIENT_BONUS): 		$(CLIENT_OBJS_BONUS) $(PRINTF)
							$(CC) $(CFLAGS) $(CLIENT_OBJS_BONUS) $(PRINTF) -o client_bonus
$(SERVER_BONUS): 		$(SERVER_OBJS_BONUS) $(PRINTF)
							$(CC) $(CFLAGS) $(SERVER_OBJS_BONUS) $(PRINTF) -o server_bonus

clean:
							make clean -C ft_printf
							$(RM) $(CLIENT_OBJS) $(SERVER_OBJS)
							$(RM) $(CLIENT_OBJS_BONUS) $(SERVER_OBJS_BONUS)
			
fclean: 				clean
							make fclean -C ft_printf
							$(RM) $(CLIENT) $(SERVER)
							$(RM) $(CLIENT_BONUS) $(SERVER_BONUS)

re:						fclean all

bonus:					$(CLIENT_BONUS) $(SERVER_BONUS)