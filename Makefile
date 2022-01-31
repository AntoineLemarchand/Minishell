define compiling
	@printf 'Compiling %s\n' $1
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
endef

define building
	@printf '%s\n' "-> Building $1"
	@make -sC $1 > /dev/null
	@echo "√"
endef

define finishing
	@printf 'Finishing %s\n' $1
	@$(CC) $(CFLAGS) $(CPPFLAGS) $2 -o $1 $(LIBS)
endef

define cleaning
	@echo -n Cleaning
	@printf '\n\t%s\n' $1
	@make $2 -sC $1 > /dev/null
endef

define removing
	@printf ' %s ' $1
	@$(RM) $1 > /dev/null
endef

SRCS			= $(addprefix srcs/, \
					main.c \
					echo.c \
					executils.c \
					)

OBJS			= $(SRCS:.c=.o)

NAME			= minishell

RM				= rm -f

CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g

CPPFLAGS		= -Iincludes

LIBS			= libft/libft.a

%.o : %.c
				$(call compiling,$<,$(<:.c=.o),0)

${NAME}:		$(OBJS)
				$(call building,libft)
				$(call finishing,$(NAME), $(OBJS))

all:			$(NAME)

clean:	
				@echo -n Removing
				$(call cleaning,libft,fclean)
				$(call removing,$(OBJS))

fclean:			clean
				$(call removing,$(NAME))

re:				fclean all
