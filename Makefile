SRCS				= 	srcs/main/main.c \
						srcs/utils/utils.c \
						srcs/utils/opperand.c \
						srcs/error/error.c \
						srcs/program/begin.c \
						srcs/program/hub.c \
						srcs/program/end.c \
						srcs/node/node.c \
						srcs/parsing/parsing.c \
						srcs/parsing/parsing.digest.c \
						srcs/parsing/parsing.base64.c \
						srcs/parsing/parsing.cipher.c \
						srcs/parsing/parsing.genrsa.c \
						srcs/md5/md5.c \
						srcs/md5/hash.c \
						srcs/sha256/sha256.c \
						srcs/sha256/hash.c \
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