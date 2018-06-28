# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 21:33:56 by tduquesn          #+#    #+#              #
#    Updated: 2018/06/25 19:38:56 by tduquesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf
LFT		=	libft.a


PLATFORM=	LINUX
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

#LMLX		=	libmlx_$(PLATFORM).a

ifeq ($(PLATFORM),LINUX)
DBFLAGS =	-fsanitize=address
LIBASAN =	-lasan
LOC_LX	=	/usr/lib/x86_64-linux-gnu/
LIB_SUFF=	_Linux
LOC_LMLX=	../../
LIBS	=	$(LIBASAN) -lm -L$(LOC_LMLX) -lmlx$(LIB_SUFF) -L$(LFTDIR) -lft -L$(LOC_LX) -lX11 -lXext
else
DBFLAGS =	
LIBASAN =
LOC_LX	=	/usr/X11/lib
LIB_SUFF=
LOC_LMLX=
LIBS	=	-lmlx -framework OpenGL -framework AppKit -L$(LFTDIR) -lft
endif


HDRDIR	=	./
LFTDIR	=	./libft/
TSTDIR	=	./tests/

HDRS	=	fdf.h					\
			get_next_line.h
SRCS	=	reader_fdf.c			\
			bresenham.c				\
			image_utils.c			\
			event_handlers.c		\
			camera.c				\
			projectors.c			\
			color.c					\
			coordinates.c
OBJS	=	$(SRCS:.c=.o)

MAIN	=	main_fdf.c
OBJ_MAIN=	$(MAIN:.c=.o)

TST_DIR		=	unit_tests
TST_MAIN	=	$(TST_DIR)/unit_tests.c
TST_EXEC	=	test.out

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

$(NAME): $(LFTDIR)$(LFT) $(OBJS) $(OBJ_MAIN)
	@printf "Compiling fdf: "$@" -> "$(RED)
	@$(CC) $(CFLAGS) -c $(MAIN) -I$(HDRDIR)
	@$(CC) $(CFLAGS) $(DBFLAGS) $(OBJS) $(OBJ_MAIN) $(LIBS) -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR)

#dependencies are taken care of in libft's makefile.
$(LFTDIR)$(LFT):
	$(MAKE) -C $(LFTDIR) $(LFT)

all: $(NAME)

clean:
	@rm -f $(OBJS) $(OBJ_MAIN)

fclean:clean
	@rm -f $(LFTDIR)$(LFT)
	@rm -f $(NAME)

re:fclean all

test:$(LFTDIR)$(LFT) $(OBJS)
	@$(CC) $(CFLAGS) $(DBFLAGS) $(OBJS) $(TST_MAIN) $(LIBASAN) -lm -lmlx$(LIB_SUFF) -L$(LFTDIR) -lft -L. -lX11 -L$(LOC_LX) -lXext -L$(LOC_LX) -o $(TST_EXEC)
	./$(TST_EXEC)
	@rm -f $(TST_MAIN:.c=.o) $(TST_EXEC)

mf_debug:
	@cat -e -t -v Makefile

.PHONY: all clean re test vlqtest capstest
