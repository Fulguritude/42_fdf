# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 21:33:56 by tduquesn          #+#    #+#              #
#    Updated: 2018/04/26 15:35:27 by tduquesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf
LFT		=	libft.a


PLATFORM=	LINUX
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

MLX		=	libmlx_$(PLATFORM).a


ifeq ($(PLATFORM),LINUX)
DBFLAGS =	-fsanitize=address
LIBASAN =	-lasan
LOC_LX	=	/usr/lib/x86_64-linux-gnu/
LIB_SUFF=	_Linux
else
DBFLAGS =	
LIBASAN =
LOC_LX	=
LIB_SUFF=
endif


HDRDIR	=	./
LFTDIR	=	./libft/
TSTDIR	=	./tests/

HDRS	=	fdf.h
SRCS	=	main_fdf.c
OBJS	=	$(SRCS:.c=.o)

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"


$(NAME): $(OBJS)
	@printf "Compiling fdf: "$@" -> "$(RED)
	@$(CC) $(CFLAGS) -c $(SRCS) -I$(HDRDIR)
	@$(CC) $(CFLAGS) $(OBJS) -lmlx$(LIB_SUFF) -L. -lX11 -L$(LOC_LX) -lXext -L$(LOC_LX) -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

#dependencies are taken care of in libft's makefile.
$(LFTDIR)$(LFT):
	$(MAKE) -C $(LFTDIR) $(LFT)

all: $(NAME)

clean:
	#@$(MAKE) -C $(LFTDIR) clean
	@rm -f $(OBJS)

fclean:clean
	#@rm -f $(LFTDIR)$(LFT)
	@rm -f $(NAME)

re:fclean all

#remove CFLAGS below before testing weirder undefined printf cases
test:$(NAME)
	./$(NAME)

mf_debug:
	@cat -e -t -v Makefile

.PHONY: all clean re test vlqtest capstest
