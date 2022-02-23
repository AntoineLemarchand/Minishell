define compiling
	@printf 'Compiling %s\n' $1
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
endef

define building
	@printf '%s\n' "Building $1"
	@make -sC $1 > /dev/null
endef

define finishing
	@printf 'Finishing %s\n' $1
	@$(CC) $(CFLAGS) $(CPPFLAGS) $2 -o $1 $(LIBS)
endef

define cleaning
	@echo -n Cleaning
	@printf ' %s\n' $1
	@make $2 -sC $1 > /dev/null
endef

define removing
	@printf ' %s\n' $1
	@$(RM) $1 > /dev/null
endef

SRCS			= $(addprefix srcs/, \
					lexer_utils.c \
					lexer.c \
					parser_cmd_utils.c \
					parser_utils.c \
					parser.c \
					main.c \
					)

OBJS			= $(SRCS:.c=.o)

NAME			= minishell

RM				= rm -f

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

CPPFLAGS		= -Iincludes

LIBS			= -lreadline libft/libft.a

%.o : %.c
				$(call compiling,$<,$(<:.c=.o),0)

${NAME}:		$(OBJS)
				$(call building,libft)
				$(call finishing,$(NAME), $(OBJS))

all:			$(NAME)

clean:	
				$(call cleaning,libft,fclean)
				@echo -n Removing
				$(call removing,$(OBJS))

fclean:			clean
				$(call removing,$(NAME))

re:				fclean all
