MEM			= $(addprefix mem/, \
				ft_memset.c \
			  	ft_bzero.c \
			  	ft_memcpy.c \
			  	ft_memmove.c \
			  	ft_memchr.c \
			  	ft_memcmp.c \
			  	ft_calloc.c \
				)

CHAR		= $(addprefix char/, \
				ft_isalpha.c \
			  	ft_isdigit.c \
			  	ft_isalnum.c \
			  	ft_isascii.c \
			  	ft_isprint.c \
			  	ft_toupper.c \
			  	ft_tolower.c \
				)

STR			= $(addprefix str/, \
				ft_strlcpy.c \
			  	ft_strlcat.c \
			  	ft_strmapi.c \
			  	ft_striteri.c \
			  	ft_strdup.c \
			  	ft_substr.c \
			  	ft_strjoin.c \
			  	ft_strjoinfree.c \
			  	ft_strtrim.c \
			  	ft_strnstr.c \
			  	ft_split.c \
			  	ft_strlen.c \
			  	ft_strchr.c \
			  	ft_strrchr.c \
			  	ft_strncmp.c \
				)

NBR			= $(addprefix nbr/, \
			ft_atoi.c \
			  	ft_itoa.c \
				)

PUT			= $(addprefix put/, \
				ft_putchar_fd.c \
			  	ft_putstr_fd.c \
			  	ft_putendl_fd.c \
			  	ft_putnbr_fd.c \
				)


LST			= $(addprefix lst/, \
				ft_lstnew.c \
			  	ft_lstadd_front.c \
			  	ft_lstsize.c \
			  	ft_lstlast.c \
			  	ft_lstadd_back.c \
			  	ft_lstdelone.c \
			  	ft_lstclear.c \
			  	ft_lstiter.c \
			  	ft_lstmap.c \
				)

SRCS		= $(addprefix srcs/, \
				${MEM} \
			  	${CHAR} \
			  	${STR} \
			  	${NBR} \
			  	${PUT} \
				${LST} \
				)

OBJS		= ${SRCS:.c=.o}

NAME		= libft.a

RM			= rm -f

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -I includes

%.c%.o:
			${CC} ${CFLAGS} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}

bonus:		${OBJS}
			ar rcs ${NAME} ${OBJS}

clean:	
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
