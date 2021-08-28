SRCS				= 	srcs/program/main.c \
						srcs/utils/utils.c \
						srcs/utils/opperand.c \
						srcs/error/error.c \
						srcs/program/hub.c \
						srcs/node/node.c \
						srcs/parsing/parsing.c \
						srcs/parsing/parsing.digest.c \
						srcs/parsing/parsing.base64.c \
						srcs/parsing/parsing.cipher.c \
						srcs/parsing/parsing.genrsa.c \
						srcs/digest/digest.c \
						srcs/digest/md5.c \
						srcs/digest/sha256.c \
						srcs/base64/base64.c \
						srcs/base64/encrypt.c \
						srcs/base64/decrypt.c \
						srcs/des/des.c \
						srcs/rsa/genrsa.c \

OBJS				= ${SRCS:.c=.o}

NAME				= ft_ssl

FLAGS				= -Wall -Wextra -Werror

all :				${NAME}

${NAME} :			${OBJS}
					gcc -o ${NAME} ${FLAGS} ${SRCS}

clean :				
					rm -rf ${OBJS}

fclean : 			clean
					rm -rf ${NAME}

re :				fclean all

.PHONY:				all clean fclean re