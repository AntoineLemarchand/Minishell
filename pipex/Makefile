define compiling
	@echo -n "$(shell tput bold)$(shell tput setaf 3)Compiling $1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $1 -o $2
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define finishing
	@echo -n "$(shell tput bold)$(shell tput setaf 2)Finishing $1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $2 -o $1
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define removing
	@echo -n "$(shell tput bold)$(shell tput setaf 8)Removing $1 $(shell tput sgr0)"
	@$(RM) $1 > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

SRCS		= $(addprefix srcs/, \
			  	ft_split.c \
				pipe.c \
			  	utils.c \
				free.c \
				parse.c \
			  	main.c \
				)

OBJS		= $(SRCS:.c=.o)


NAME		= pipex

RM			= rm -f

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g

CPPFLAGS	= -Iincludes

%.o : %.c
			$(call compiling,$<,$(<:.c=.o),0)

${NAME}:	$(OBJS)
			$(call finishing,$(NAME),$(OBJS))

all:		$(NAME)

bonus:		all

clean:	
			$(call removing,$(OBJS))

fclean:		clean
			$(call removing,$(NAME))

re:			fclean all
