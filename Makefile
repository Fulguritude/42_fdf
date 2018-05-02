# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/17 21:52:48 by fulguritu         #+#    #+#              #
#    Updated: 2018/04/17 21:53:08 by fulguritu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 21:33:56 by tduquesn          #+#    #+#              #
#    Updated: 2018/02/20 16:20:25 by tduquesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf
LFT		=	libft.a

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
DBFLAGS =	-fsanitize=address
#PLATFORM=	-DLINUX

HDRDIR	=	./
LFTDIR	=	./libft/
TSTDIR	=	./tests/

HDRS	=	mlx.h						\
			fdf.h
SRCS	=	
OBJS	=	$(SRCS:.c=.o)

MAIN	=	main_fdf.c
TEST	=	test.out

$(NAME): $(LFT) $(OBJS)
	@printf "Compiling library: "$@" -> "$(RED)
	@cp $(LFTDIR)$(LFT) ./$@
	@$(CC) $(CFLAGS) -c $(SRCS) -I$(HDRDIR)
	@ar -r $@ $(OBJS)
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

#dependencies are taken care of in libft's makefile.
$(LFT):
	$(MAKE) -C $(LFTDIR) $(LFT)

all: $(NAME)

clean:
	@printf "Calling libftprintf clean...\n"
	@$(MAKE) -C $(LFTDIR) clean
	@rm -f $(OBJS)
	@rm -f $(TSTDIR)$(MAIN:.c=.o)
	@rm -f $(TEST)

fclean:clean
	@printf "Calling fdf fclean...\n"
	@rm -f $(LFTDIR)$(LFT)
	@rm -f $(NAME)

re:fclean all

#remove CFLAGS below before testing weirder undefined printf cases
test:$(NAME)
	@printf "Rebuilding test.out for rule 'test'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(MAIN) -o $(TSTDIR)$(MAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(MAIN:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	@printf "Done ! Usage: ""\033[0;32m""./test.out""\033[0m""\n"

capstest:$(NAME)
	@printf "Rebuilding test.out for rule 'capstest'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(CAPSMAIN) -o $(TSTDIR)$(CAPSMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(CAPSMAIN:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	@printf "Done ! Usage: ""\033[0;32m""./test.out {value|NULL}""\033[0m""\n"

vlqtest:$(NAME)
	@printf "Rebuilding test.out for rule 'vlqtest'...\n"
	@$(CC) $(CFLAGS) $(DBFLAGS) -c $(TSTDIR)$(VLQMAIN) -o $(TSTDIR)$(VLQMAIN:.c=.o)
	@$(CC) $(OBJS) $(TSTDIR)$(VLQMAIN:.c=.o) -lftprintf -L./ -lasan -o $(TEST)
	./$(TEST)
	@make clean
	@printf "Done !\n"

.PHONY: all clean re test vlqtest capstest
