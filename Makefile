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

HDRS	=	fdf.h					\
			algebra.h				\
			get_next_line.h
SRCS	=	get_next_line.c			\
			reader_fdf.c			\
			bresenham.c				\
			quaternion_products.c	\
			image_utils.c			\
			event_handlers.c		\
			vec3_op.c				\
			mat33_op.c				\
			mat44_op.c				\
			coordinates.c			\
			camera.c				\
			projectors.c			\
			color.c
OBJS	=	$(SRCS:.c=.o)

MAIN	=	main_fdf.c
OBJ_MAIN=	$(MAIN:.c=.o)

TST_DIR		=	unit_tests
TST_MAIN	=	$(TST_DIR)/unit_tests.c
TST_EXEC	=	test.out

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

$(NAME): $(LFTDIR)$(LFT) $(OBJS)
	@printf "Compiling fdf: "$@" -> "$(RED)
	@$(CC) $(CFLAGS) -c $(MAIN) -I$(HDRDIR)
	@$(CC) $(CFLAGS) $(DBFLAGS) $(OBJS) $(LIBASAN) -lm -lmlx$(LIB_SUFF) -L$(LFTDIR) -lft -L. -lX11 -L$(LOC_LX) -lXext -L$(LOC_LX) -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS) -I$(HDRDIR)

#dependencies are taken care of in libft's makefile.
$(LFTDIR)$(LFT):
	$(MAKE) -C $(LFTDIR) $(LFT)

all: $(NAME)

clean:
	#@$(MAKE) -C $(LFTDIR) clean
	@rm -f $(OBJS) $(OBJ_MAIN)

fclean:clean
	#@rm -f $(LFTDIR)$(LFT)
	@rm -f $(NAME)

re:fclean all

#remove CFLAGS below before testing weirder undefined printf cases
test:$(LFTDIR)$(LFT) $(OBJS)
	@$(CC) $(CFLAGS) $(DBFLAGS) $(OBJS) $(TST_MAIN) $(LIBASAN) -lm -lmlx$(LIB_SUFF) -L$(LFTDIR) -lft -L. -lX11 -L$(LOC_LX) -lXext -L$(LOC_LX) -o $(TST_EXEC)
	./$(TST_EXEC)
	@rm -f $(TST_MAIN:.c=.o) $(TST_EXEC)

mf_debug:
	@cat -e -t -v Makefile

.PHONY: all clean re test vlqtest capstest
