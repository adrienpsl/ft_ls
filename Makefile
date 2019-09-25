#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#              #
#    Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls
LIBFTDIR = libft/render/
INCSDIR = includes/
SRCSDIR = src/
OBJSDIR = objs/
CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	ft_ls.build_files.c \
        ft_ls.build_files.utils_0.c \
        ft_ls.build_files.utils_1.c \
        ft_ls.build_files.utils_2.c \
        ft_ls.c \
        ft_ls.catch_options.c \
        ft_ls.handle_files_array.c \
        ft_ls.parser.c \
        ft_ls.print.c \
        ft_ls.utlis.c \
        main.c

OBJS = $(addprefix $(OBJSDIR),$(SRCS:.c=.o))

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -I $(INCSDIR) -I $(LIBFTDIR)$(INCSDIR) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIBFTDIR) -lft

clean:
	rm -rf $(OBJSDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
